
#ifndef BOOKSTORE_REAL_SRC_DIARY_H_
#define BOOKSTORE_REAL_SRC_DIARY_H_

#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>

struct record {
  int type;
  char who_did_it[61];
  char did_what[100];
  record(const int &_type = 0, const std::string &_who = "", const std::string &_what = "") {
    type = _type;
    strcpy(who_did_it, _who.c_str());
    strcpy(did_what, _what.c_str());
  }
  friend std::ostream &operator<<(std::ostream &os, const record &out) {
    if (out.type == 1) os << "\x1b[34;1m" << "user system -- ";
    if (out.type == 2) os << "\x1b[34;1m" << "finance system -- ";
    os << "\x1b[32;1m" << (std::string) out.who_did_it << " ";
    os << "\x1b[0m" << (std::string) out.did_what;
    return os;
  }
};

class Diary {
 private:
  std::fstream stream;
  std::string name;
  int now_size = 0;
 public:
  Diary() = default;
  Diary(const std::string &_name) {
    name = _name;
    stream.open(name);
    stream.seekg(0, std::ios::beg);
    if (!stream) {
      stream.close();
      stream.open(name, std::ios::out);
      stream.write(reinterpret_cast<char *>(&now_size), sizeof(int));
      stream.close();
    } else {
      stream.close();
    }
  }
  ~Diary() {
    stream.close();
  }
  inline void initialize(const std::string &_name) {
    name = _name;
    stream.open(name);
    stream.seekg(0, std::ios::beg);
    if (!stream) {
      stream.close();
      stream.open(name, std::ios::out);
      stream.write(reinterpret_cast<char *>(&now_size), sizeof(int));
      stream.close();
    } else {
      stream.close();
    }
  }

  inline void PushBack(const int &_type, const std::string &who, const std::string &what) {
    stream.open(name);
    stream.seekg(0);
    stream.read(reinterpret_cast<char *>(&now_size), sizeof(int));
    stream.seekp(sizeof(int) + now_size * sizeof(record));
    record to_insert(_type, who, what);
    stream.write(reinterpret_cast<char *>(&to_insert), sizeof(record));
    stream.seekp(0);
    ++now_size;
    stream.write(reinterpret_cast<char *>(&now_size), sizeof(int));
    stream.close();
  }

  inline void Traverse() {
    stream.open(name);
    stream.seekg(0);
    stream.read(reinterpret_cast<char *>(&now_size), sizeof(int));
    record all_information[now_size];
    stream.read(reinterpret_cast<char *>(&all_information), sizeof(all_information));
    std::cout << "\x1b[33;1m" << "-------------------------------viewing log-------------------------------" << '\n';
    for (int i = 0; i < now_size; ++i) {
      std::cout << all_information[i] << '\n';
    }
    std::cout << "\x1b[33;1m" << "-------------------------------------------------------------------------" << '\n';
  }
};

#endif //BOOKSTORE_REAL_SRC_DIARY_H_
