# Bookstore's 开发文档

*By BruceLee*

*Bookstore*是一个**书店管理系统**，面向书店的管理者们和受众们，用于提供方便的图书检索与购买相关服务。

## 修改日志

*22.12.4* 新建文档，并进行了架构和基本的思考

*22.12.14* 完成块状链表，修改了文件存储部分的内容

*22.12.23* 完成主题逻辑部分，修改了主体逻辑部分的内容

*22.12.25* 完成了log和一些细节的处理，细化了开发文档

## 程序功能概述

1、**交互功能**：我们在命令行中进行读入和输出。我们的程序将检测这些指令，也就是根据需求文档中的正则语法规则判断一行输入的合法性，倘若不合法，抛出异常。

2、**账户系统**：账户系统储存的是每一个账户的各种信息，包括名称、ID、权限、密码；

​    我们实现的操作有：登陆账户、注销账户、注册账户、修改密码、创建账户、删除账户。

​    其中，值得注意的是，

3、**图书系统**：图书系统提供图书信息、库存剩余、交易记录等信息

​	我们实现的操作有：检索图书（以索书号升序）、购买图书、选择图书、修改图书信息、图书进货。

4、**日志系统**：我们可以在其中查看交易笔数、查询财务记录、并生成”赏心悦目的“日志记录。

## 主题逻辑说明

我们在主程序中进行一个循环，在循环体内进行对每一行信息的处理。同时进行进行一个**try...catch**的结构来获取报错信息，并进行输出。

当然，我需要实现一个类似于process_line的函数来进行不同指令的处理。在这个函数中，我们通过文件输入来通过对应类中对应的函数接口来修改/增加部分数据。

## 代码文件结构

函数分为如下几个部分，main函数，tokenscanner，针对不同类型的指令处理（例如账户相关、图书相关、购买相关、日志相关、错误抛出/处理相关）。（具体实现待补充）

而含有的类也主要包括：图书、账户、日志、登陆状态、指令语句（Statement基类和派生类）。

文件主要包括账户、图书、日志、登陆状态、tokenscanner等文件

## 各类接口、成员说明

**Bookstore**

```C++
private:
	Books all_books;
	Users all_users;
	Finance_system finance_system;
	Employee_system employee_system;
public:
	Bookstore();
	void run(const string &command);
	void quit();
	void buy(vector<string> &key_list);
	void select(vector<string> &key_list)
    void edit(vector<string> &key_list)
    void add_user(vector<string> &key_list)
    void login(vector<string> &key_list)
```



**TokenScanner**

```C++
TokenScanner(std::istream &infile) // constructor via files

~TokenScanner // delocate the storage

bool hasMoreTokens()

std::string nextToken() // get the next piece of information

void saveToken(std::string token) // push the token back
```

**Login**

```c++
// members
std::vector<std::string> current_users;
std::stac<std::string> users;
// member functions
login() // initialize the stack
~login()
void enroll (std::string name) // login of a user(will check validity)
void exit() // exit the current layer of login
std::String get_user_name()
```

**User**

```C++
enum user_state {guest = 0, customer = 1, staff = 3, administrator= 7};
private:
	char id,password,name;
public:
	user_state power;
	User();
	User(const string &id_, const string &name_, const string &password_, const user_state & power);
	void edit_password(const string &);
```

**Books**

```C++
friend ostream &operator<<(ostream &, const Books &);
private:
	char keyword,name,author,isbn;
	long long rest;
	double price;
public:
	Books();
	const string isbn();
	const string name();
	const string keyword();
	const double &price();
	const long long &rest();
	
	// there're also functions for data modification
```

**Error**

```C++
std::string message;
ErrorException(std::string message) {
	this->message = message;
}
void error(stdd::string message) // send the error message
```

**Logging**

```C++
char *operator_id; // who did this
bool result; // whether it succeeded
char *cmd; // store the commands
int time; // when it was done
friend ostream &operator<<(ostream &, const Log &);
Log();
```

## 文件储存

运行中的输出信息会输出到对应类的文档中