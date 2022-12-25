# Bookstore's 开发文档

*By BruceLee*

*Bookstore*是一个**书店管理系统**，面向书店的管理者们和受众们，用于提供方便的图书检索与购买相关服务。

## 代码风格

使用 Google 风格

## 修改日志

*22.12.4* 新建文档，并进行了架构和基本的思考

*22.12.14* 完成块状链表库，修改了部分文件存储部分的内容

*22.12.21* 完成大部分主体逻辑部分，修改了部分主体逻辑部分的内容

*22.12.22* 完成账户类的撰写，修改了部分主体逻辑部分的内容

*22.12.25* 完成了log和一些细节的处理，细化了开发文档

## 程序功能概述

1、**交互功能**：我们在命令行中进行读入和输出。我们的程序将检测这些指令，也就是根据需求文档中的正则语法规则判断一行输入的合法性，倘若不合法，抛出异常。

2、**图书系统**：图书系统提供ISBN号、图书信息、库存剩余、关键词、价格、书本名称、作者这些信息。

3、**账户系统**：账户系统储存的是每一个账户的各种信息，包括名称、ID、权限、密码；

​    我们实现的操作有：登陆账户、注销账户、注册账户、修改密码、创建账户、删除账户。

​    其中，值得注意的是，该*bookstore*支持嵌套登录，所以我们用std::vector实现了登录栈，登录栈中记录了现有登录的账户以及他们所选中的书籍和是否选择的状态。

**（这里用到了缓存的思想，若用户连续地对选中的书目modify时可以有效地减小文件读写次数）**

​	我们对用户支持的对图书的操作有：检索图书的各种信息（例如ISBN,名称，作者，关键词）（以索书号升序）、购买图书、选择图书、修改图书信息、图书进货。

4、**日志系统**：我们可以在财务记录中查询最近任意次数的交易，也可以遍历所有交易得到所有收入和支出的总和。

​	另外，我们同样在管理员账号下可以通过**log**操作来获得赏心悦目的日志记录（2022.12.25完成）

## 主题逻辑说明

我们在主程序中进行一个循环，在循环体内进行对每一行信息的处理。同时进行进行一个**try...catch**的结构来获取报错信息，并进行输出。

同时，我实现了**"explain.h"**这一个头文件，在其中我们经过切片来。在这个函数中，我们通过文件输入来通过对应类中对应的函数接口来修改/增加部分数据。

## 代码文件结构

我们由**main.cpp**连接至**explain.h**，再通过**explain.h**链接到**program.h**中的program类的各种成员函数，而program类中则内嵌了图书类、账户类、财务记录类和日志类，而前两个类的存储是基于块状链表的（**MyUll.h**）

下面是我的repository的文件结构

```plain
├── src
│   ├── main.cpp
│   ├── Utils
│   │   ├── ErrorException.h
│   │   ├── book.h
│   │   ├── account.h
│   │   ├── log.h
│   │   ├── diary.h
│   │   ├── program.h
│   │   ├── MyUll.h
│   │   └── explain.h
├── demostration of log.in
├── CMakeLists.txt
├── document.md
├── README.md
```

## 各类接口、成员说明

**MyUll.h**(基于块状链表的文件存储，使用了模板类来方便各种类型的文件存储)

```C++
template<class T>
struct books { // 这里的书泛化地指代存储的信息
  char name[65];
  T value;
  inline friend bool operator<(const books &cmp_1, const books &cmp_2);
  inline friend bool operator>=(const books &cmp_1, const books &cmp_2);
  books(const std::string &index, const T &number);
}
template<class T>
struct node {
  int current_size = 0;
  books<T> small_books[317];
};
template<class T>
struct begin_info { // 存储index，方便确定块的查找
  int now_size = 0;
  int start_place = sizeof(begin_info);
  int end_place = sizeof(begin_info);
  int block_storage[633];
  books<T> last_book[633];
};
template<class T>
const int block_size = sizeof(node<T>);
const int max_size = 316;
const int out_size = 158;
template<class T>
class unrolled_linklist {
 private :
  std::fstream file_stream;
  std::string file_name;
  begin_info<T> start;
 public:
  explicit unrolled_linklist() = default;
  explicit unrolled_linklist(const std::string &_file_name);
  inline void Insert(const std::string &index, const T &value);
  inline std::vector<T> Find(const std::string &index);
  inline void ShowAll();
  inline void Delete(const std::string &index, const T &value);
}
```

**log.h**（基于文件存储的账本记录）

```C++
class Log {
 private:
  std::fstream log_stream;
  std::string log_name;
  struct info {
    int now_size = 0;
    double all_information[1005] = {0};
  } everything;
 public:
  Log() = default;
  Log(const std::string &_log_name);
  ~log();
  inline void initialize(const std::string &_log_name);
  // 初始化
  inline void Insert(double finance);
  //记录一笔交易
  inline void ShowFinance(const int &count = -1);
  // 默认是-1，指代全部展示财务记录
}
```

**diary.h**(基于文件存储的日志记录)

```C++
struct record {
  int type;
  char who_did_it[61];
  char did_what[100];
}
// 用来记录一个操作，里面存储了操作的位置、操作者和操作内容
class Diary {
 private:
  std::fstream stream;
  std::string name;
  int now_size = 0;
 public:
  Diary() = default;
  Diary(const std::string &_name);
  inline void initialize(const std::string &_name);
  inline void PushBack(const int &_type, const std::string &who, const std::string &what);
  inline void Traverse();
}
```

**Program.h**（包含了一切有关bookstore的操作）

```C++
class Program {
 public:
  // members
  unrolled_linklist<User> user_store;
  unrolled_linklist<Book> book_store;
  unrolled_linklist<Book> name_bookstore;
  unrolled_linklist<Book> author_bookstore;
  unrolled_linklist<Book> keyword_bookstore;
  Diary my_diary;
  Log finance;
  std::vector<User> login_stack;
  int current_privilege = 0; // 现有权限等级，用于判断某用户是否能调用某函数
  // functions
  Program();
  void Login(const std::string &id, const std::string &password = "");
  void Logout();
  void Register(const std::string &userid, const std::string &password, const std::string &username);
  void ModifyPassword(const std::string &id, const std::string &new_password,
                      const std::string &current_password = "");
  void AddUser(const std::string &userid,
               const std::string &password,
               const std::string &privilege,
               const std::string &username);
  void DeleteUser(const std::string &userid);
  void Exit();
  void Quit();
  void Select(const std::string &_ISBN);
  void Buy(const std::string &_ISBN, int number);
  void Import(const int &quantity, const double &total_cost);
  void Show(const int &way, const std::string &content);
  void Modify(const std::vector<std::pair<int, std::string>> &todo);
  void Erase(const Book &eraser);
  void Input(const Book &in);
};
```

**explain.h** (单行语句的判断，以及执行函数)

```C++
int StringToUnsignedInt(const std::string &input);
bool UnsignedIntCheck(const std::string &input);
std::pair<int, std::string> ParseShow(const std::string &input);
// 用于方便地解析show语句
std::pair<int, std::string> ParseModify(const std::string &input);
std::vector<std::string> Decompose(const std::string &input);
// 将输入语句按照切片分开
void Execute(Program &program, const std::vector<std::string> &input);
// 将这些切片放入程序执行
```

**account.h**

```C++
bool UserNameCheck(const std::string &_name);
bool UserInfoCheck(const std::string &_info);
bool PrivilegeCheck(const std::string &_privilege);
class User {
  friend class Program;
 protected:
  char UserID[31];
  char Password[31];
  char Username[31];
  int privilege;
  Book selected;
  bool choosing = false;
 public:
  User(
      const std::string &_privilege = "1",
      const std::string &_UserID = "",
      const std::string &_Password = "",
      const std::string &_Username = "");
  void ChangePassword(const std::string &new_password);
  User &operator=(const User &cmp);
  friend bool operator<(const User &cmp_1, const User &cmp_2);
}
```

**books.h**（设计了图书类，并加入了信息有效性的判断函数）

```C++
bool ISBNCheck(const std::string &_ISBN);
// 其余信息的有效性判断
// 包括名称、作者和关键词
bool BookInfoCheck(const std::string &info);
// 对于关键词的解析
std::vector<std::string> ParseKeywords(const std::string &keyword);
// 检查关键词的正确性
bool CheckKeywords(const std::string &keyword);
// 检查单个关键词的正确性
bool SingleKeywordCheck(const std::string &keyword);
class Book {
  friend class Program;
 private:
  char ISBN[21] = "";
  char BookName[61] = "";
  char Author[61] = "";
  char Keyword[61] = "";
  double price = 0;
  long long storage = 0;
 public:
  Book();
  void ChangeISBN(const std::string &_ISBN);
  void ChangeName(const std::string &_name);
  void ChangeAuthor(const std::string &_author);
  void ChangeKeyword(const std::string &_keyword);
  void ChangePrice(const double &_price);
  friend bool operator<(const Book &cmp_1, const Book &cmp_2);
  friend bool operator==(const Book &cmp_1, const Book &cmp_2);
  friend std::ostream &operator<<(std::ostream &os, const Book &out);
  // 格式化地输出图书信息
```

## 文件储存说明

  所有的输出文件都是由program类完成的

```plain
├── users（块状链表，存储用户信息）
├── books（块状链表，以ISBN为键值存储书本信息）
├── names（块状链表，以书名为键值存储书本信息）
├── authors（块状链表，以作者为键值存储书本信息）
├── keywords（块状链表，以关键词为键值存储书本信息，同时一本书会因为有多个关键词而被重复存入）
├── records（存储财务信息）
├── diary（存储一切的操作信息）
```

## 致谢

感谢@lauyeeyu对我的鼓励和支持，以及对我块状链表疑惑的解答

感谢@zsq259在我看requirements.md时对我许多奇怪问题的耐心解答

感谢@whr-a、 @jpppppppppppppppppppppppp 和我的讨论和互相支持