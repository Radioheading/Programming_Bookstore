//
// Created by 18221 on 2022/12/21.
//

#ifndef BOOKSTORE_REAL__BOOK_H_
#define BOOKSTORE_REAL__BOOK_H_

#include <string>
#include "ErrorException.h"
#include <cstring>
#include <iomanip>

const int MaxISBNLen = 20;
const int MaxInfoLen = 60;

// check the validity of ISBN
bool ISBNCheck(const std::string &_ISBN) {
  if (_ISBN.length() > MaxISBNLen) return false;
  for (int i = 0; i < _ISBN.length(); ++i) {
    if (_ISBN[i] < 33 || _ISBN[i] == 127) return false;
  }
  return true;
}

// check the validity of other information
bool BookInfoCheck(const std::string &info) {
  if (info.length() > MaxInfoLen) return false;
  for (int i = 0; i < info.length(); ++i) {
    if (info[i] < 33 || info[i] == 34 || info[i] == 127) return false;
  }
  return true;
}

std::vector<std::string> ParseKeywords(const std::string &keyword) {
  std::unordered_set<std::string> existed;
  std::vector<std::string> result;
  if (!BookInfoCheck(keyword)) {
    throw ErrorException();
  }
  std::string temp;
  for (int i = 0; i < keyword.size(); ++i) {
    if (keyword[i] == '|') {
      if (temp == "" || existed.find(temp) != existed.end()) {
        throw ErrorException();
      } else {
        existed.insert(temp);
        //std::cout<<temp<<'\n';
        result.push_back(temp);
        temp = "";
      }
    } else {
      temp += keyword[i];
    }
  }
  if (temp != "" && existed.find(temp) == existed.end()) {
    //std::cout<<temp<<'\n';
    result.push_back(temp);
  } else {
    throw ErrorException();
  }
  return result;
}
bool CheckKeywords(const std::string &keyword) {
  std::unordered_set<std::string> existed;
  std::vector<std::string> result;
  if (!BookInfoCheck(keyword)) {
    return false;
  }
  std::string temp;
  for (int i = 0; i < keyword.size(); ++i) {
    if (keyword[i] == '|') {
      if (temp == "" || existed.find(temp) != existed.end()) {
        return false;
      } else {
        existed.insert(temp);
        result.push_back(temp);
        temp = "";
      }
    } else {
      temp += keyword[i];
    }
  }
  if (temp != "" && existed.find(temp) == existed.end()) {
    result.push_back(temp);
  } else {
    return false;
  }
  return true;
}
void SingleKeywordCheck(const std::string &keyword) {
  if (!BookInfoCheck(keyword)) throw ErrorException();
  if (keyword.find('|') == std::string::npos) throw ErrorException();
}

class Book {
  friend class Program;
 protected:
  char ISBN[21] = "";
  char BookName[61] = "";
  char Author[61] = "";
  char Keyword[61] = "";
  double price = 0;
  int storage = 0;
 public:
  Book(const std::string &_ISBN = "") {
    strcpy(ISBN, _ISBN.c_str());
    price = 0;
    storage = 0;
  }
  void ChangeISBN(const std::string &_ISBN) {
    if (!ISBNCheck(_ISBN)) throw ErrorException();
    memset(ISBN, 0, sizeof(ISBN));
    strcpy(ISBN, _ISBN.c_str());
  }
  void ChangeName(const std::string &_name) {
    if (!BookInfoCheck(_name)) throw ErrorException();
    memset(BookName, 0, sizeof(BookName));
    strcpy(BookName, _name.c_str());
  }
  void ChangeAuthor(const std::string &_author) {
    if (!BookInfoCheck(_author)) throw ErrorException();
    memset(Author, 0, sizeof(Author));
    strcpy(Author, _author.c_str());
  }
  void ChangeKeyword(const std::string &_keyword) {
    if (!BookInfoCheck(_keyword)) throw ErrorException();
    memset(Keyword, 0, sizeof(Keyword));
    strcpy(Keyword, _keyword.c_str());
  }
  void ChangePrice(const double &_price) {
    price = _price;
  }

  friend bool operator<(const Book &cmp_1, const Book &cmp_2) {
    return (std::string) cmp_1.ISBN < (std::string) cmp_2.ISBN;
  }
  friend bool operator==(const Book &cmp_1, const Book &cmp_2) {
    return (std::string) cmp_1.ISBN == (std::string) cmp_2.ISBN;
  }
  friend bool operator!=(const Book &cmp_1, const Book &cmp_2) {
    return (std::string) cmp_1.ISBN != (std::string) cmp_2.ISBN;
  }
  friend std::ostream &operator<<(std::ostream &os, const Book &out) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << out.ISBN << '\t' << out.BookName << '\t' << out.Author << '\t'
    << out.Keyword << '\t'<< out.price << '\t' << out.storage << '\n';
    return os;
  }
};
#endif //BOOKSTORE_REAL__BOOK_H_
