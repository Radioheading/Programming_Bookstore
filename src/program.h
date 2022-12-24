#ifndef BOOKSTORE_REAL__PROGRAM_H_
#define BOOKSTORE_REAL__PROGRAM_H_
#include "account.h"
#include "MyUll.h"
#include "book.h"
#include <iomanip>
#include "explain.h"
#include "log.h"

double StringToDouble(const std::string &input) {
  if (input.length() > 13) throw ErrorException();
  bool dot = false;
  if (input.size() == 1 && input[0] == '0') return 0;
  if (input[0] == '.') throw ErrorException();
  if (input.size() > 1) {
    if (input[0] == '0' && input[1] == '0') throw ErrorException();
    if (input[0] == '0' && input[1] != '.') throw ErrorException();
  }
  for (int i = 0; i < input.size(); ++i) {
    if (input[i] == '.') {
      if (!dot) dot = true;
      else throw ErrorException();
    } else {
      if (input[i] > '9' || input[i] < '0') {
        throw ErrorException();
      }
    }
  }
  return std::stod(input);
}

bool DoubleCheck(const std::string &input) {
  if (input.length() > 13) return false;
  bool dot = false;
  if (input.size() == 1 && input[0] == '0') return false;
  if (input[0] == '.') return false;
  if (input.size() > 1) {
    if (input[0] == '0' && input[1] == '0') return false;
    if (input[0] == '0' && input[1] != '.') return false;
  }
  for (int i = 0; i < input.size(); ++i) {
    if (input[i] == '.') {
      if (!dot) dot = true;
      else return false;
    } else {
      if (input[i] > '9' || input[i] < '0') {
        return false;
      }
    }
  }
  return true;
}
//--------------------------Class Program---------------------------------
// this class stores everything of a bookstore system
// its member functions involve all the possible operations in a bookstore
//-----------------------------------------------------------------------*/
class Program {
 public:
  // members
  unrolled_linklist<User> user_store;
  unrolled_linklist<Book> book_store;
  unrolled_linklist<Book> name_bookstore;
  unrolled_linklist<Book> author_bookstore;
  unrolled_linklist<Book> keyword_bookstore;
  Log finance;
  std::vector<User> login_stack;
  int current_privilege = 0;
  // functions
  Program();
  void Login(const std::string &id, const std::string &password = "kind of confident");
  void Logout();
  void Register(const std::string &userid, const std::string &password, const std::string &username);
  void ModifyPassword(const std::string &id, const std::string &new_password, const std::string &current_password = "");
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

void Program::Erase(const Book &eraser) {
  book_store.Delete(eraser.ISBN, eraser);
  name_bookstore.Delete(eraser.BookName, eraser);
  author_bookstore.Delete(eraser.Author, eraser);
  if (((std::string) eraser.Keyword).empty()) {
    keyword_bookstore.Delete("", eraser);
  } else {
    std::vector<std::string> todo = ParseKeywords(eraser.Keyword);
    for (int i = 0; i < todo.size(); ++i) {
      keyword_bookstore.Delete(todo[i], eraser);
    }
  }
}
void Program::Input(const Book &in) {
  book_store.Insert(in.ISBN, in);
  name_bookstore.Insert(in.BookName, in);
  author_bookstore.Insert(in.Author, in);
  if (((std::string) in.Keyword).empty()) {
    keyword_bookstore.Insert("", in);
  } else {
    std::vector<std::string> todo = ParseKeywords(in.Keyword);
    for (int i = 0; i < todo.size(); ++i) {
      keyword_bookstore.Insert(todo[i], in);
    }
  }
}

// start-up of the program
Program::Program() {
  current_privilege = 0;
  user_store.initialize("users");
  book_store.initialize("books");
  name_bookstore.initialize("names");
  author_bookstore.initialize("authors");
  keyword_bookstore.initialize("keywords");
  finance.initialize("records");
  User super_admin("7", "root", "sjtu");
  if (user_store.Find("root").empty()) {
    user_store.Insert("root", super_admin);
  }
}
void Program::Login(const std::string &id, const std::string &password) {
  std::vector<User> exist_check = user_store.Find(id);
  if (exist_check.empty()) {
    throw ErrorException();
  } else {
    if (exist_check[0].Password != password && password != "kind of confident") {
      throw ErrorException();
    } else { // successful Login!
      if (current_privilege <= exist_check[0].privilege && password == "kind of confident") {
        throw ErrorException();
      }
      login_stack.push_back(exist_check[0]);
      current_privilege = exist_check[0].privilege;
    }
  }
}

void Program::Logout() {
  if (current_privilege < 1) throw ErrorException();
  if (login_stack.empty()) throw ErrorException();
  else {
    if (login_stack.size() > 1) {
      current_privilege = login_stack[login_stack.size() - 2].privilege;
    } else {
      current_privilege = 0;
    }
    login_stack.pop_back();
  }
}

void Program::Register(const std::string &userid, const std::string &password, const std::string &username) {
  if (!user_store.Find(userid).empty()) {
    throw ErrorException();
  } else {
    if (!UserNameCheck(username) || !UserInfoCheck(password) || !UserInfoCheck(userid)) {
      throw ErrorException();
    }
    User another("1", userid, password, username);
    user_store.Insert(userid, another);
  }
}
void Program::ModifyPassword(const std::string &id,
                             const std::string &new_password,
                             const std::string &current_password) {
  if (current_privilege < 1) throw ErrorException();
  std::vector<User> modify = user_store.Find(id);
  if (modify.empty()) throw ErrorException();
  if ((std::string) modify[0].Password != current_password
      && current_privilege != 7)
    throw ErrorException();
  if (!UserInfoCheck(new_password)) {
    throw ErrorException();
  }
  user_store.Delete(id, modify[0]);
  modify[0].ChangePassword(new_password);
  user_store.Insert(id, modify[0]);
}
void Program::AddUser(const std::string &userid,
                      const std::string &password,
                      const std::string &privilege,
                      const std::string &username) {
  if (current_privilege < 3 || privilege[0] - 48 >= current_privilege) throw ErrorException();
  if (!user_store.Find(userid).empty()) throw ErrorException();
  if (!PrivilegeCheck(privilege) || !UserNameCheck(username)
      || !UserInfoCheck(password) || !UserInfoCheck(userid)) {
    throw ErrorException();
  }
  User added_user(privilege, userid, password, username);
  user_store.Insert(userid, added_user);
}
void Program::DeleteUser(const std::string &userid) {
  if (current_privilege < 7) throw ErrorException();
  std::vector<User> search = user_store.Find(userid);
  if (search.empty()) throw ErrorException();
  for (int i = 0; i < login_stack.size(); ++i) {
    if ((std::string) login_stack[i].UserID == userid) throw ErrorException();
  }
  user_store.Delete(userid, search[0]);
}
void Program::Exit() {
  login_stack.clear();
  current_privilege = 0;
}
void Program::Quit() {
  login_stack.clear();
  current_privilege = 0;
}
void Program::Select(const std::string &_ISBN) {
  if (current_privilege < 3) throw ErrorException();
  if (!ISBNCheck(_ISBN)) throw ErrorException();
  std::vector<Book> search = book_store.Find(_ISBN);
  if (search.empty()) {
    Book another(_ISBN);
    Input(another);
    login_stack.back().selected = another;
    login_stack.back().choosing = true;
  } else {
    login_stack.back().selected = search[0];
    login_stack.back().choosing = true;
  }
}
void Program::Buy(const std::string &_ISBN, int number) {
  if (current_privilege < 1) throw ErrorException();
  std::vector<int> identical;
  std::vector<Book> search = book_store.Find(_ISBN);
  if (search.empty()) throw ErrorException();
  if (search[0].storage < number) throw ErrorException();
  Erase(search[0]);
  search[0].storage -= number;
  for (int i = 0; i < login_stack.size(); ++i) {
    if (login_stack[i].choosing && login_stack[i].selected.ISBN == _ISBN) {
      login_stack[i].selected.storage -= number;
    }
  }
  Input(search[0]);
  std::cout << std::fixed << std::setprecision(2);
  std::cout << search[0].price * number << '\n';
  finance.Insert(search[0].price * number);
}
void Program::Import(const int &quantity, const double &total_cost) {
  if (current_privilege < 3 || !login_stack.back().choosing) {
    throw ErrorException();
  }
  Book duplicate = login_stack.back().selected;
  std::vector<int> identical;
  for (int i = 0; i < login_stack.size(); ++i) {
    if (login_stack[i].choosing && login_stack[i].selected == duplicate) {
      identical.push_back(i);
    }
  }
  Erase(login_stack.back().selected);
  login_stack.back().selected.storage += quantity;
  for (int i : identical) {
    login_stack[i].selected = login_stack.back().selected;
  }
  // record this in the log system
  finance.Insert(-total_cost);
  Input(login_stack.back().selected);
}
void Program::Show(const int &way, const std::string &content) {
  if (current_privilege < 1) throw ErrorException();
  std::vector<Book> search;
  if (way == 1) {
    if (!ISBNCheck(content)) {
      throw ErrorException();
    }
    search = book_store.Find(content);
  }
  if (way == 2) {
    if (!BookInfoCheck(content)) {
      throw ErrorException();
    }
    search = name_bookstore.Find(content);
  }
  if (way == 3) {
    if (!BookInfoCheck(content)) {
      throw ErrorException();
    }
    search = author_bookstore.Find(content);
  }
  if (way == 4) {
    if (!SingleKeywordCheck(content)) {
      throw ErrorException();
    }
    search = keyword_bookstore.Find(content);
  }
  if (search.empty()) std::cout << '\n';
  else {
    for (int i = 0; i < search.size(); ++i) {
      std::cout << search[i];
    }
  }
}
void Program::Modify(const std::vector<std::pair<int, std::string>> &todo) {
  if (current_privilege < 3 || !login_stack.back().choosing) {
    throw ErrorException();
  }
  Erase(login_stack.back().selected);
  Book duplicate = login_stack.back().selected;
  std::vector<int> identical;
  for (int i = 0; i < login_stack.size(); ++i) {
    if (login_stack[i].choosing && login_stack[i].selected == duplicate) {
      identical.push_back(i);
    }
  }
  for (int i = 0; i < todo.size(); ++i) {
    if (todo[i].first == 1) {
      if (login_stack.back().selected.ISBN == todo[i].second) {
        Input(duplicate);
        login_stack.back().selected = duplicate;
        throw ErrorException();
      } else {
        if (!book_store.Find(todo[i].second).empty() || !ISBNCheck(todo[i].second)) {
          Input(duplicate);
          login_stack.back().selected = duplicate;
          throw ErrorException();
        } else {
          login_stack.back().selected.ChangeISBN(todo[i].second);
        }
      }
    }
    if (todo[i].first == 2) {
      if (!BookInfoCheck(todo[i].second)) {
        Input(duplicate);
        login_stack.back().selected = duplicate;
        throw ErrorException();
      }
      login_stack.back().selected.ChangeName(todo[i].second);
    }
    if (todo[i].first == 3) {
      if (!BookInfoCheck(todo[i].second)) {
        Input(duplicate);
        login_stack.back().selected = duplicate;
        throw ErrorException();
      }
      login_stack.back().selected.ChangeAuthor(todo[i].second);
    }
    if (todo[i].first == 4) {
      if (!CheckKeywords(todo[i].second)) {
        Input(duplicate);
        login_stack.back().selected = duplicate;
        throw ErrorException();
      }
      login_stack.back().selected.ChangeKeyword(todo[i].second);
    }
    if (todo[i].first == 5) {
      if (!DoubleCheck(todo[i].second) && todo[i].second != "0") {
        Input(duplicate);
        login_stack.back().selected = duplicate;
        throw ErrorException();
      }
      login_stack.back().selected.ChangePrice(StringToDouble(todo[i].second));
    }
    for (int i : identical) {
      login_stack[i].selected = login_stack.back().selected;
    }
  }
  Input(login_stack.back().selected);
}
#endif //BOOKSTORE_REAL__PROGRAM_H_
