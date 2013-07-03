var ajaxReq = new AjaxRequest();
var record = new Array();
var line = 1;

function submit(){
	if ($(".input")[0].value == "")
		return;

	$(".newtable")[0].style.display = "none";
	$(".result")[0].style.display = "inline-block";
	//清空之前的内容
	$(".result-table")[0].innerHTML = "";	
	//保存历史记录
	record.push($(".input")[0].value);
	var url = "php/submit.php?sql=" + $(".input")[0].value;
	url = encodeURI(encodeURI(url)); //编码，避免传送时乱码
	ajaxReq.send("GET", url, true, function(){ XMLHandler(submitHandler); }, "application/x-www-form-urlencoded; charset=UTF-8");
	$(".input")[0].value = "";
}

function XMLHandler(handler){
    if(ajaxReq.getReadyState() === 4 && ajaxReq.getStatus() === 200){
		//var str = ajaxReq.getResponseText().Trim();
		//alert(str);
	    ajaxReq.send("GET", "xml/data.xml", true, handler);
	}
}

function submitHandler(){
	if(ajaxReq.getReadyState() === 4 && ajaxReq.getStatus() === 200){
		var tr = document.createElement("tr");
		tr.className = "columns";
		$(".result-table")[0].appendChild(tr);
		//测试info
		var info = getText(ajaxReq.getResponseXML().getElementsByTagName("info")[0]);
		if (info != ""){
			tr.innerHTML = info;
			return;
		}
	    //获取列内容
		var columns = ajaxReq.getResponseXML().getElementsByTagName("columns")[0];
		var column = columns.getElementsByTagName("column");		
				
		for (var i = 0; i < column.length; i++){
			var th = document.createElement("th");
			th.innerHTML = getText(column[i]);
			tr.appendChild(th);
		}
		//获取行内容
		var rows = ajaxReq.getResponseXML().getElementsByTagName("row");
		for (var i = 0; i < rows.length; i++){
			var tr = document.createElement("tr");
			var data = rows[i].getElementsByTagName("data");
			for (var j = 0; j < data.length; j++){
				var td = document.createElement("td");
				td.innerHTML = getText(data[j]);
				tr.appendChild(td);
			}
			$(".result-table")[0].appendChild(tr);
		}
	}
}

//获取节点文本
function getText(elem) {
    var text = "";
    if (elem) {
        if (elem.childNodes) {
            for (var i = 0; i < elem.childNodes.length; i++) {
                var child = elem.childNodes[i];
                if (child.nodeValue){
                    text += child.nodeValue;
                } else {
                    if (child.childNodes[0]){
                        if (child.childNodes[0].nodeValue){
                            text += child.childNodes[0].nodeValue;
			}
		    }	
                }
            }
        }
    }
    return text;
}

function history(){
	$(".newtable")[0].style.display = "none";
	$(".result")[0].style.display = "inline-block";
	//清空之前的内容
	$(".result-table")[0].innerHTML = "";
	
	for (var i = 0; i < record.length; i++){
		var p = document.createElement("p");
		p.innerHTML = record[i];
		$(".result-table")[0].appendChild(p);
	}
}

function create(){
	//初始化line
	line = 1;
	
	$(".result")[0].style.display = "none";
	$(".newtable")[0].style.display = "inline-block";
	
	var url = "php/submit.php?sql=SELECT dbname FROM dictionary.databases;";
	url = encodeURI(encodeURI(url)); //编码，避免传送时乱码
	ajaxReq.send("GET", url, true, function(){ XMLHandler(nameHandler); }, "application/x-www-form-urlencoded; charset=UTF-8");
}

function nameHandler(){
	if(ajaxReq.getReadyState() === 4 && ajaxReq.getStatus() === 200){
		var data = ajaxReq.getResponseXML().getElementsByTagName("data");
		$(".database")[0].innerHTML = "";
		//alert(data.length);
		for (var i = 0; i < data.length; i++){
			var option = document.createElement("option");
			option.innerHTML = getText(data[i]);
			$(".database")[0].appendChild(option);
		}
	}
}

function newLine(){
	line++;
	var p = document.createElement("p");
	p.innerHTML = "<input class='TDark-input columnname' type='text' placeholder='Column Name...' />&nbsp;&nbsp;\
						<select class='datatype' onchange='charNum(this)'>\
							<option value='INT'>INT</option>\
							<option value='DOUBLE'>DOUBLE</option>\
							<option value='CHAR'>CHAR</option>\
						</select>&nbsp;&nbsp;\
						<input class='TDark-input charnum disable' type='text' placeholder='Number...' disabled='true'/>&nbsp;&nbsp;\
						<span class='TDark-checkbox'>\
							<input type='checkbox' class='primary' id='primary" + line + "' name='ckeckbox' />\
							<label for='primary" + line + "' data-on='a'></label>&nbsp;\
							<span class='tip'> Primary Key</span>\
						</span>\
						<span class='TDark-checkbox'>\
							<input type='checkbox' class='notnull' id='notnull" + line + "' name='ckeckbox' />\
							<label for='notnull" + line + "' data-on='a'></label>&nbsp;\
							<span class='tip'> Not Null</span>\
						</span>\
						<span class='TDark-checkbox'>\
							<input type='checkbox' class='unique' id='unique" + line + "' name='ckeckbox' />\
							<label for='unique" + line + "' data-on='a'></label>&nbsp;\
							<span class='tip'> Unique</span>\
						</span>\
						<input class='TDark-input fktable' type='text' placeholder='FKtable...' />&nbsp;&nbsp;\
						<input class='TDark-input fkcolumn' type='text' placeholder='FKcolumn...' />&nbsp;&nbsp;\
						<a class='delete TB02 TB02-black' onclick='deleteColumn(this)'> Delete</a>";
	$(".create-form")[0].appendChild(p);
}

function charNum(ele){
	var charnum = TFunc.nextNode(ele);
	if (ele.value == "CHAR"){
		charnum.disabled = false;
		TFunc.removeClass(charnum, "disable");
	} else {
		charnum.disabled = true;
		charnum.value = "";
		TFunc.addClass(charnum, "disable");
	}
}

function generate(){
	var sql = "CREATE TABLE ";
	sql += $(".database")[0].value + "." + $(".tablename")[0].value + "(";

	var col = $(".create-form")[0].getElementsByTagName("p");
	for (var i = 0; i < col.length; i++){
		if (col[i].getElementsByClassName("columnname")[0].value == ""){
			alert("Column name can not be empty!");
			return;
		}
		sql += col[i].getElementsByClassName("columnname")[0].value;
		sql += " " + col[i].getElementsByClassName("datatype")[0].value;
		if (col[i].getElementsByClassName("charnum")[0].value != ""){
			sql += "(" + col[i].getElementsByClassName("charnum")[0].value + ")";
		}
		if (col[i].getElementsByClassName("primary")[0].checked){
			sql += " PRIMARY KEY";
		}
		if (col[i].getElementsByClassName("notnull")[0].checked){
			sql += " NOT NULL";
		}
		if (col[i].getElementsByClassName("unique")[0].checked){
			sql += " UNIQUE";
		}
		if (col[i].getElementsByClassName("fktable")[0].value != "" && col[i].getElementsByClassName("fkcolumn")[0].value != ""){
			sql += " FOREIGN KEY REFERENCES " + col[i].getElementsByClassName("fktable")[0].value + "(" + col[i].getElementsByClassName("fkcolumn")[0].value + ")";
		}
		if (i < col.length-1){
			sql += ",";
		}
	}
	sql += ");";
	$(".input")[0].value = sql;
}

function deleteColumn(ele){
	var p = ele.parentNode;
	$(".create-form")[0].removeChild(p);
}
