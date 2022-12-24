#ifndef BOOKSTORE_REAL__EXPLAIN_H_
#define BOOKSTORE_REAL__EXPLAIN_H_

#include <string>
#include <vector>
#include <iostream>
#include "ErrorException.h"
#include <unordered_set>
#include "program.h"

/*------------------------------explain.h-------------------------
 * the head file mainly focuses on the separation of the operation
 * line, so as to execute them
 * -------------------------------------------------------------*/


// func: StringToUnsignedInt
// check the validity of the string and make it an unsigned
// integer if it can be converted
int StringToUnsignedInt(const std::string &input) {
  if (input.length() > 10) throw ErrorException();
  long long ans = 0;
  if (input.size() > 1 && input[0] == '0') throw ErrorException();
  for (int i = 0; i < input.length(); ++i) {
    if (input[i] > 57 || input[i] < 48) throw ErrorException();
    else ans = ans * 10 + input[i] - 48;
  }
  if (ans == 0 || ans > 2147483647) throw ErrorException();
  return (int) ans;
}
bool UnsignedIntCheck(const std::string &input) {
  if (input.length() > 10) return false;
  long long ans = 0;
  if (input.size() > 1 && input[0] == '0') return false;
  for (int i = 0; i < input.length(); ++i) {
    if (input[i] > 57 || input[i] < 48) return false;
    else ans = ans * 10 + input[i] - 48;
  }
  if (ans == 0 || ans > 2147483647) return false;
  return true;
}

// func: ParseShow
// parse the show operations into the showing type and
// the showing keywords
std::pair<int, std::string> ParseShow(const std::string &input) {
  if (input[0] != '-') {
    throw ErrorException();
  }
  if (input.find('=') == std::string::npos) {
    throw ErrorException();
  }
  std::string temp;
  int i, type;
  for (i = 1; i < input.length(); ++i) {
    if (input[i] == '=') break;
    else temp += input[i];
  }
  ++i;
  if (temp == "ISBN") type = 1;
  else if (temp == "name") type = 2;
  else if (temp == "author") type = 3;
  else if (temp == "keyword") type = 4;
  else {
    throw ErrorException();
  }
  if (type != 1) {
    if (input.length() < i + 2 || input[i] != '"' || input[input.length() - 1] != '"') {
      throw ErrorException();
    }
    temp = "";
    ++i;
    for (; i < input.length() - 1; ++i) {
      temp += input[i];
    }
  } else {
    if (input.length() < i) throw ErrorException();
    temp = "";
    for (; i < input.length(); ++i) {
      temp += input[i];
    }
  }
  return std::make_pair(type, temp);
}

std::pair<int, std::string> ParseModify(const std::string &input) {
  if (input[0] != '-') {
    throw ErrorException();
  }
  if (input.find('=') == std::string::npos) {
    throw ErrorException();
  }
  std::string temp;
  int i, type;
  for (i = 1; i < input.length(); ++i) {
    if (input[i] == '=') break;
    else temp += input[i];
  }
  ++i;
  if (temp == "ISBN") type = 1;
  else if (temp == "name") type = 2;
  else if (temp == "author") type = 3;
  else if (temp == "keyword") type = 4;
  else if (temp == "price") type = 5;
  else {
    throw ErrorException();
  }
  if (type != 1 && type != 5) {
    if (input.length() <= i + 2 || input[i] != '"' || input[input.length() - 1] != '"') {
      throw ErrorException();
    }
    temp = "";
    ++i;
    for (; i < input.length() - 1; ++i) {
      temp += input[i];
    }
  } else {
    if (input.length() < i + 1) throw ErrorException();
    temp = "";
    for (; i < input.length(); ++i) {
      temp += input[i];
    }
  }
  return std::make_pair(type, temp);
}

// the set of all the possible operations
std::unordered_set<std::string> reserved =
    {"quit", "exit", "su", "logout", "register",
     "passwd", "useradd", "delete", "show", "buy",
     "select", "modify", "import", "show", "log"};

std::vector<std::string> Decompose(const std::string &input) {
  std::vector<std::string> ans;
  std::string temp = "";
  int i;
  for (i = 0; i < input.length(); ++i) {
    if (input[i] == ' ') continue;
    else break;
  }
  for (int j = i; j < input.length(); ++j) {
    //if (input[j] < 32 || input[j] == 127) throw ErrorException();
    if (input[j] == ' ') {
      if (temp != "") {
        ans.push_back(temp);
        temp = "";
      }
    } else {
      temp += input[j];
    }
  }
  if (temp != "") {
    ans.push_back(temp);
  }
  if (ans.empty()) return ans;
  if (reserved.find(ans[0]) == reserved.end()) throw ErrorException();
  if (ans[0] == "quit" && ans.size() != 1) throw ErrorException();
  if (ans[0] == "exit" && ans.size() != 1) throw ErrorException();
  if (ans[0] == "logout" && ans.size() != 1) throw ErrorException();
  if (ans[0] == "select" && ans.size() != 2) throw ErrorException();
  if (ans[0] == "su" && ans.size() != 2 && ans.size() != 3) throw ErrorException();
  if (ans[0] == "exit" && ans.size() != 1) throw ErrorException();
  if (ans[0] == "register" && ans.size() != 4) throw ErrorException();
  if (ans[0] == "passwd" && ans.size() != 3 && ans.size() != 4) throw ErrorException();
  if (ans[0] == "useradd" && ans.size() != 5) throw ErrorException();
  if (ans[0] == "delete" && ans.size() != 2) throw ErrorException();
  if (ans[0] == "select" && ans.size() != 2) throw ErrorException();
  if (ans[0] == "buy" && ans.size() != 3) throw ErrorException();
  if (ans[0] == "show" && ans.size() > 3) throw ErrorException();
  if (ans[0] == "modify" && (ans.size() > 6 || ans.size() < 2)) throw ErrorException();
  return ans;
}

void Execute(Program &program, const std::vector<std::string> &input) {
  if (input.empty()) return;
  if (input[0] == "quit") {
    program.Quit();
  }
  if (input[0] == "exit") {
    program.Exit();
  }
  if (input[0] == "su") {
    if (input.size() == 2) {
      program.Login(input[1]);
    } else {
      program.Login(input[1], input[2]);
    }
  }
  if (input[0] == "logout") {
    program.Logout();
  }
  if (input[0] == "register") {
    program.Register(input[1], input[2], input[3]);
  }
  if (input[0] == "passwd") {
    if (input.size() == 3) {
      program.ModifyPassword(input[1], input[2]);
    } else {
      program.ModifyPassword(input[1], input[3], input[2]);
    }
  }
  if (input[0] == "useradd") {
    program.AddUser(input[1], input[2], input[3], input[4]);
  }
  if (input[0] == "delete") {
    program.DeleteUser(input[1]);
  }
  if (input[0] == "select") {
    program.Select(input[1]);
  }
  if (input[0] == "buy") {
    program.Buy(input[1], StringToUnsignedInt(input[2]));
  }
  if (input[0] == "import") {
    program.Import(StringToUnsignedInt(input[1]), StringToDouble(input[2]));
  }
  if (input[0] == "show") {
    if (input.size() == 1) {
      if (program.current_privilege < 1) throw ErrorException();
      program.book_store.ShowAll();
    } else {
      if (input[1] == "finance") {
        if (program.current_privilege < 7) throw ErrorException();
        if (input.size() == 2) {
          program.finance.ShowFinance(-1);
        }
        if (input.size() == 3) {
          if (input[2] == "0") {
            program.finance.ShowFinance(0);
          } else {
            program.finance.ShowFinance(StringToUnsignedInt(input[2]));
          }
        }
      } else {
        program.Show(ParseShow(input[1]).first, ParseShow(input[1]).second);
      }
    }
  }
  if (input[0] == "modify") {
    std::vector<std::pair<int, std::string>> commands;
    for (int i = 1; i < input.size(); ++i) {
      commands.push_back(ParseModify(input[i]));
    }
    program.Modify(commands);
  }
}

#endif //BOOKSTORE_REAL__EXPLAIN_H_
