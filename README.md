#Confaid

A very very simpilified relational DB for application software design course.

##NOTE
We are still in code period now, so it can't work yet.

##Compile

###Linux

To compile, we need **glib2.0** and **flex** package. Use to yum or apt-get to install these packages. For example:

`yum install -y flex bison glib2 glib2-devel`

and use make to compile:

`make`

###Windows

Windows is a little more complicated.

- Visit [The GTK+ Project](http://www.gtk.org/download/win32.php) to download Glib. Confaid needs at least `libglib-2.0-0.dll` and `intl.dll`
- Vist [Parser Generator](http://www.bumblebeesoftware.com/) to download Parser Generator, in which Confaid needs `yl.lib`
- Rename all .c to .cpp if you use Microsoft Visual C++

After necessary libraries are ready, use a whatever compiler to compile.

##What is Confaid?

Confaid means Confucious Said. Black humor, uh-huh :-)