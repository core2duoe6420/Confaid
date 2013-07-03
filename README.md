#Confaid

A very very simpilified relational DB for application software design course.

##Compile

###Linux

To compile, we need **glib2.0** and **flex** package. Use to yum or apt-get to install these packages. For example:

	# yum install -y flex bison glib2 glib2-devel

and use make to compile:

	# make

###Windows

Windows is a little more complicated.

- Visit [The GTK+ Project](http://www.gtk.org/download/win32.php) to download Glib. Confaid needs at least `libglib-2.0-0.dll` and `intl.dll`
- Vist [Parser Generator](http://www.bumblebeesoftware.com/) to download Parser Generator, in which Confaid needs `yl.lib`
- Rename all .c to .cpp if you use Microsoft Visual C++

After necessary libraries are ready, use a whatever compiler to compile.

##How to use
Confaid provides a **socket** interface. Any program can access to Confaid with socket api. We provide a web interface using php socket in the package.

To run Confaid engine, execute Confaid and input server ip and port, Confaid will listen the ip address. 

The client program should first connect Confaid and write the socket with SQL statement, and read result from the socket. The result represents as XML format, with node `info` `columns` `row`, and a string **"end"** as an end mark. for example:

	<info>1 row affected</info>end

or (note: CR is only for good-looking, there is no CR in actual data.)


	<info></info>
	<columns>
		<column>id</column>
		<column>name</column>
	</columns>
	<row>
		<data>1</data>
	</row>
	<row>
		<data>test</data>
	</row>
	end

##Supported SQL
Confaid supports only a very simplified SQL and the key word must be upper character. Here is the support list:

- Simple query, projection and join
- Create database and table
- Insert delete update record
- Only INT DOUBLE and CHAR(n) data type is supported
- Simple WHERE statement, IS NULL or NOT NULL is not supported
- UNIQUE and FOREGIN KEY constraint and NULL value is partly supported
- Alias and self join is not supported
- Primary key and index is not supported
- Modify or drop column is not supported

For example, the following SQL is acceptable:

	CREATE DATABASE school;
	USE school;
	CREATE TABLE student(
		id INT PRIMARY KEY,
		name CHAR(16) NOT NULL,
		age INT NOT NULL,
		sex INT NOT NULL
	);
	CREATE TABLE course(
		id INT PRIMARY KEY,
		name CHAR(16) NOT NULL
	);
	CREATE TABLE selected_course(
		id INT PRIMARY KEY,
		stu INT NOT NULL FOREIGN KEY REFERENCES student(id),
		cou INT NOT NULL FOREIGN KEY REFERENCES course(id)
	);	

	INSERT INTO student VALUES(1,'John',20,1);
	INSERT INTO course VALUES(1,'math');
	INSERT INTO selected_course VALUES(1,1,1);

	SELECT student.name
	FROM student,selected_course 
	WHERE student.id==selected_course.stu;
##What is Confaid?

>Confaid means Confucious Said. Black humor, uh-huh :-)