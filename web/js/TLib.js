/** ------------------------------------------------------------------------------
* TLib js
* @version 1.0
* @Explain 封装了一些底层功能的js API以及一些js内置类的扩展
* @author  alwaysonlinetxm
* @email   txm19921005@126.com 
* --------------------------------------------------------------------------------
*/

/** 
* 选择器函数
* 功能：接收以'#','.'开头或不带前缀的字符串，分别获取对应id，class以及tag的元素/元素列表
* 参数：以'#','.'开头的id，class或不带前缀的tag
* 返回：参数字符串所对应的元素/元素列表
*/
function $(ele){
	switch (ele.slice(0, 1)){
		case "#": return document.getElementById(ele.slice(1));
			break;
		case ".": return document.getElementsByClassName(ele.slice(1));
			break;
		default: return document.getElementsByTagName(ele);
			break;
	}
}

/**
* 静态功能类
* PS: 该类伪静态类，所有属性和方法都是为了实现某个特定功能，完全与外部独立
*/
var TFunc = function(){};

/**
* 属性配置函数
* 功能：对指定对象的指定属性进行属性配置，配置值、可枚举性、可写性、可配置性
* 参数：待配置得对象，要配置的属性数组(可选)，属性配置对象
* 返回：配置完的对象
* PS：当不指定任何属性时，默认对所有属性进行配置
*/
TFunc.config = function(obj){
    if (typeof obj == "object"){
		if (arguments.length == 2){
			var names = Object.getOwnPropertyNames(obj);
			var configs = arguments[1];
		} else if (arguments.length == 3 && Array.isArray(arguments[1])){
		    var names = arguments[1];
			var configs = arguments[2];
		}		
		names.forEach(function(n){   //检测是否有此自有属性，有则进行设置
		    if (obj.hasOwnProperty(n)) Object.defineProperty(obj, n, configs);
		});
	}
	return obj;
} 

/**
* 事件注册函数
* 功能：为指定元素注册指定的事件
* 参数：待注册的元素，待注册的事件类型字符串，绑定的函数
* 返回：无
* PS：该函数可为单个元素的同个事件注册绑定多个函数，同时不支持addEventListener和attachEvent除外
*/
TFunc.on = function(elem, type, func){
    if (elem.addEventListener){
        elem.addEventListener(type, func, false);
    } else if (elem.attachEvent){
        elem.attachEvent('on'+type, func);
    } else {
	    elem["on"+type] = func;
	}
}

/**
* 样式获取函数
* 功能：获取指定元素的当前CSSStyleDeclaration对象，适用于内联样式，内部样式，外部样式
* 参数：待配置的元素，第二个可选的伪元素信息
* 返回：元素的CSSStyleDeclaration对象
*/
TFunc.getStyle = function(obj, fake){
	fake = fake ? fake : null;
    return window.getComputedStyle ? window.getComputedStyle(obj, fake) : obj.currentStyle;
}

/**
* 浏览器类型判断函数
* 功能：获取浏览器类型
* 参数：无
* 返回：浏览器类型字符串
*/
TFunc.browser = function(){
    if (navigator.userAgent.indexOf("MSIE") >= 0){
        return "MSIE"; 
    }
    if (navigator.userAgent.indexOf("Firefox") >= 0){
        return "Firefox"; 
    }
    if (navigator.userAgent.indexOf("Opera") >= 0){
        return "Opera"; 
    }
	if (navigator.userAgent.indexOf("Chrome") >= 0){
        return "Chrome"; 
    }
    if (navigator.userAgent.indexOf("Safari") >= 0) { 
        return "Safari"; 
    } 
    if (navigator.userAgent.indexOf("Camino") >= 0){ 
        return "Camino"; 
    } 
    if (navigator.userAgent.indexOf("Gecko") >=0 ){ 
        return "Gecko"; 
    } 
}

/**
* 文件类型匹配函数
* 功能：将传入文件名与指定后缀名进行匹配，判断类型是否匹配
* 参数：fname为文件名(可包含路径)，参数types为包含允许类型的数组，如["jpg", "png", "gif"]
* 返回：匹配则返回ture，否则返回false
*/
TFunc.checkFileType = function(fname, types){
    var last = fname.slice(fname.lastIndexOf(".")+1).toLowerCase();
	for (var key in types){
	    if (last == types[key].toLowerCase()) return true;
	}
	return false;
}

/**
* canvas检测函数
* 功能：检测是否支持canvas元素
* 参数：无
* 返回：支持则返回ture，否则返回false
*/
TFunc.isCanvasEnable = function(){
    return !!document.createElement('canvas').getContext;
}

/**
* class添加/删除函数
* 功能：添加/删除class
* 参数：待操作的元素以及待添加/删除的类名
* 返回：无
*/
//添加类
TFunc.addClass = function(ele, className){
    if (!new RegExp('(^|\\s+)'+className).test(ele.className)){
		ele.className += " " + className;
	}
}
//删除类
TFunc.removeClass = function(ele, className){
    ele.className = ele.className.replace(new RegExp('(^|\\s+)'+className), "");
}

/**
* 兄弟节点获取函数
* 功能：获取指定节点的前/后兄弟节点，跳过文本
* 参数：指定的节点
* 返回：前/后兄弟节点
*/
//获取前兄弟节点
TFunc.previousNode = function(ele){
	var pre = ele.previousSibling;
	while (pre.nodeName == "#text"){
		pre = pre.previousSibling;
	}
	return pre;
}
//获取后兄弟节点
TFunc.nextNode = function(ele){
	var next = ele.nextSibling;
	while (next.nodeName == "#text"){
		next = next.nextSibling;
	}
	return next;
}

/**
* String类扩展
* 功能：去除字符串的前导，后导空格
* 参数：无
* 返回：去除空格后的字符串
*/
//除去前后空格
String.prototype.Trim = String.prototype.trim || function(){ 
    return this.replace(/(^\s*)|(\s*$)/g, ""); 
} 
//除去前导空格
String.prototype.LTrim = function(){ 
    return this.replace(/(^\s*)/g, ""); 
}
//除去后导空格 
String.prototype.RTrim = function() { 
    return this.replace(/(\s*$)/g, ""); 
} 

/**
* Date类扩展
* 功能：规格化日期格式为 YY-MM-DD hh:mm:ss
* 参数：无
* 返回：规格化后的日期字符串
*/
Date.prototype.shortFormat = function() {
	var hours = "0" + this.getHours();
    var mins = "0" + this.getMinutes();
    var secs = "0" + this.getSeconds();
	
    if(hours > 9)
	   hours = this.getHours();
    if(mins > 9)
	   mins = this.getMinutes();
    if(secs > 9)
	   secs = this.getSeconds();

    return this.getFullYear() + "-" + (this.getMonth()+1)+ "-" + this.getDate() + " " + hours + ":" + mins + ":" + secs;
}