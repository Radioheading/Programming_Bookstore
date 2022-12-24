#ifndef BOOKSTORE_REAL__MYULL_H_
#define BOOKSTORE_REAL__MYULL_H_
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>

/*-----------------------------Class Unrolled_Linklist--------------------------------
 * this is a data structure which can store information in files in a comparatively
 * more convenient way, enabling us to insert/find/delete information more quickly
 * ---------------------------------------------------------------------------------*/
template<class T>
struct books {
  char name[65];
  T value;

  inline friend bool operator<(const books &cmp_1, const books &cmp_2) {
    if (std::string(cmp_1.name) < std::string(cmp_2.name)
        || std::string(cmp_1.name) == std::string(cmp_2.name) && cmp_1.value < cmp_2.value)
      return true;
    return false;
  }
  inline friend bool operator>=(const books &cmp_1, const books &cmp_2) {
    return !(cmp_1 < cmp_2) || std::string(cmp_1.name) == std::string(cmp_2.name) && cmp_1.value == cmp_2.value;
  }

  books() : name("") {
    T();
  }
  inline void initial(const std::string &index, const T &number) {
    strcpy(name, index.c_str());
    value = number;
  }
  books(const std::string &index, const T &number) {
    strcpy(name, index.c_str());
    value = number;
  }
};
template<class T>
struct node {
  int current_size = 0;
  books<T> small_books[317];
};
template<class T>
struct begin_info {
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
  explicit unrolled_linklist(const std::string &_file_name) {
    file_name = _file_name;
    file_stream.open(file_name);
    file_stream.seekg(0, std::ios::beg);
    if (!file_stream) {
      file_stream.close();
      file_stream.open(file_name, std::ios::out);
      file_stream.write(reinterpret_cast<char *>(&start), sizeof(start));
      file_stream.close();
    } else {
      file_stream.close();
    }
  }
  ~unrolled_linklist() {
    file_stream.close();
  }
  inline void initialize(const std::string &_file_name) {
    file_name = _file_name;
    file_stream.open(file_name);
    file_stream.seekg(0, std::ios::beg);
    if (!file_stream) {
      file_stream.close();
      file_stream.open(file_name, std::ios::out);
      file_stream.write(reinterpret_cast<char *>(&start), sizeof(start));
      file_stream.close();
    } else {
      file_stream.close();
    }
  }
  inline void Insert(const std::string &index, const T &value) {
    books<T> another(index, value);
    file_stream.open(file_name);
    file_stream.seekg(0);
    file_stream.read(reinterpret_cast<char *>(&start), sizeof(start));
      file_stream.seekp(start.start_place);
    if (start.now_size == 0) { // nothing exist then
      node<T> temp;
      temp.current_size = 1;
      temp.small_books[0].initial(index, value);
      file_stream.write(reinterpret_cast<char *>(&temp), sizeof(temp));
      file_stream.seekp(0);
      ++start.now_size;
      start.end_place += block_size<T>;
      start.block_storage[0] = sizeof(start);
      start.last_book[0] = another;
      file_stream.write(reinterpret_cast<char *>(&start), sizeof(start));
      file_stream.close();
      return;
    } else { // there's something in the file
      int i;
      i = std::lower_bound(start.last_book, start.last_book + start.now_size, another) - start.last_book;
      if (i == start.now_size) --i;
      node<T> current;
      file_stream.seekg(start.block_storage[i]);
      file_stream.read(reinterpret_cast<char *>(&current), sizeof(current));
      unsigned long insert_place =
          std::upper_bound(current.small_books, current.small_books + current.current_size, another)
              - current.small_books;
      for (int j = current.current_size; j > insert_place; --j) {
        current.small_books[j] = current.small_books[j - 1];
      }
      current.small_books[insert_place] = another;
      ++current.current_size;
      if (current.current_size == max_size) { // block splitting required
        node<T> new_block;
        new_block.current_size = out_size;
        current.current_size = max_size - out_size;
        for (int j = 0; j < out_size; ++j) {
          new_block.small_books[j] = current.small_books[j + max_size - out_size];
        }
        for (int j = start.now_size; j >= i + 2; --j) {
          start.block_storage[j] = start.block_storage[j - 1];
          start.last_book[j] = start.last_book[j - 1];
        }
        start.block_storage[i + 1] = start.end_place;
        start.last_book[i + 1] = new_block.small_books[new_block.current_size - 1];
        start.last_book[i] = current.small_books[current.current_size - 1];
        ++start.now_size;
        start.end_place += block_size<T>;
        file_stream.seekp(0);
        file_stream.write(reinterpret_cast<char *>(&start), sizeof(start));
        file_stream.seekp(start.block_storage[i]);
        file_stream.write(reinterpret_cast<char *>(&current), sizeof(current));
        file_stream.seekp(start.block_storage[i + 1]);
        file_stream.write(reinterpret_cast<char *>(&new_block), sizeof(new_block));
        file_stream.close();
      } else {
        file_stream.seekp(start.block_storage[i]);
        file_stream.write(reinterpret_cast<char *>(&current), sizeof(current));
        start.last_book[i] = current.small_books[current.current_size - 1];
        file_stream.seekp(0);
        file_stream.write(reinterpret_cast<char *>(&start), sizeof(start));
        file_stream.close();
      }
    }
  }

  inline std::vector<T> Find(const std::string &index) {
    books<T> another(index, T());
    std::vector<T> ans;
    file_stream.open(file_name);
    file_stream.seekg(0);
    file_stream.read(reinterpret_cast<char *>(&start), sizeof(start));
    if (start.now_size == 0 || start.last_book[start.now_size - 1] < another) {
      if (start.now_size != 0) {
      }
      file_stream.close();
      return ans;
    }
    for (int i = 0; i < start.now_size; ++i) {
      if (start.last_book[i] >= another) {
        file_stream.seekg(start.block_storage[i]);
        node<T> current;
        file_stream.read(reinterpret_cast<char *>(&current), sizeof(current));
        unsigned long find_place =
            std::lower_bound(current.small_books, current.small_books + current.current_size, another)
                - current.small_books;
        for (unsigned long j = find_place; j < current.current_size; ++j) {
          if ((std::string) current.small_books[j].name == index) {
            ans.push_back(current.small_books[j].value);
          } else break;
        }
        if (current.small_books[current.current_size - 1].name != index) break;
      }
    }
    file_stream.close();
    return ans;
  }

  inline void ShowAll() {
    file_stream.open(file_name);
    file_stream.seekg(0);
    file_stream.read(reinterpret_cast<char *>(&start), sizeof(start));
    if (start.now_size == 0) { // an empty line when there's nothing
      std::cout<<'\n';
      file_stream.close();
      return;
    }
    for (int i = 0; i < start.now_size; ++i) {
      node<T> current;
      file_stream.seekg(start.block_storage[i]);
      file_stream.read(reinterpret_cast<char *>(&current), sizeof(current));
      for (int j = 0; j < current.current_size; ++j) {
        std::cout<<current.small_books[j].value<<'\n';
      }
    }
    file_stream.close();
  }

  inline void Delete(const std::string &index, const T &value) {
    books<T> another(index, value);
    file_stream.open(file_name);
    file_stream.seekg(0);
    file_stream.read(reinterpret_cast<char *>(&start), sizeof(start));
    file_stream.seekp(start.start_place);
    if (start.now_size == 0) {
      file_stream.close();
      return;
    } else {
      int i;
      i = std::lower_bound(start.last_book, start.last_book + start.now_size, another) - start.last_book;
      if (i == start.now_size) {
        file_stream.close();
        return;
      }
      file_stream.seekg(start.block_storage[i]);
      node<T> current;
      file_stream.read(reinterpret_cast<char *>(&current), sizeof(current));
      if (current.current_size > 0
          && current.small_books[current.current_size - 1] >= another) { // we may delete things here
        unsigned long j = std::lower_bound(current.small_books, current.small_books + current.current_size, another)
            - current.small_books;
        if (j == current.current_size || current.small_books[j].name != index
            || current.small_books[j].value != value) { // it simply doesn't exist
          file_stream.close();
          return;
        }
        for (unsigned long k = j; k < current.current_size - 1; ++k) { // it exists
          current.small_books[k] = current.small_books[k + 1];
        }
        --current.current_size;
        file_stream.seekp(start.block_storage[i]);
        file_stream.write(reinterpret_cast<char *>(&current), sizeof(current));
        if (current.current_size == 0) {
          for (int k = i; k < start.now_size - 1; ++k) {
            start.last_book[k] = start.last_book[k + 1];
            start.block_storage[k] = start.block_storage[k + 1];
          }
          --start.now_size;
          file_stream.seekp(0);
          file_stream.write(reinterpret_cast<char *>(&start), sizeof(start));
        }
        file_stream.close();
        return;
      }
    }
  }
};
#endif