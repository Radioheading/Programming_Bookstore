#ifndef BOOKSTORE_REAL__LOG_H_
#define BOOKSTORE_REAL__LOG_H_
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

/*------------------------Class Log--------------------------
 * this class stores the information of the transactions,
 * and can show information like finance reports and log
 * --------------------------------------------------------*/
class Log {
 private:
  std::fstream log_stream;
  std::string log_name;
  struct info {
    int now_size = 0;
    double all_information[40005] = {0};
  } everything;
 public:
  Log() = default;
  Log(const std::string &_log_name) {
    log_name = _log_name;
    log_stream.open(log_name);
    log_stream.seekg(0, std::ios::beg);
    if (!log_stream) {
      log_stream.close();
      log_stream.open(log_name, std::ios::out);
      log_stream.write(reinterpret_cast<char *>(&everything), sizeof(everything));
      log_stream.close();
    } else {
      log_stream.close();
    }
  }
  ~Log() {
    log_stream.close();
  }
  inline void initialize(const std::string &_log_name) {
    log_name = _log_name;
    log_stream.open(log_name);
    log_stream.seekg(0, std::ios::beg);
    if (!log_stream) {
      log_stream.close();
      log_stream.open(log_name, std::ios::out);
      log_stream.write(reinterpret_cast<char *>(&everything), sizeof(everything));
      log_stream.close();
    } else {
      log_stream.close();
    }
  }

  inline void Insert(double finance) {
    log_stream.open(log_name);
    log_stream.seekg(0);
    log_stream.read(reinterpret_cast<char *>(&everything), sizeof(everything));
    everything.all_information[everything.now_size] = finance;
    ++everything.now_size;
    log_stream.seekp(0);
    log_stream.write(reinterpret_cast<char *>(&everything), sizeof(everything));
    log_stream.close();
  }

  inline void ShowFinance(const int &count = -1) {
    log_stream.open(log_name);
    log_stream.seekg(0);
    log_stream.read(reinterpret_cast<char *>(&everything), sizeof(everything));
    if (everything.now_size < count) {
      log_stream.close();
      throw ErrorException();
    }
    if (count == 0) {
      std::cout << '\n';
      log_stream.close();
      return;
    }
    double in = 0;
    double out = 0;
    if (count == -1) {
      for (int i = 0; i < everything.now_size; ++i) {
        if (everything.all_information[i] > 0) in += everything.all_information[i];
        if (everything.all_information[i] < 0) out += (-everything.all_information[i]);
      }
      std::cout << std::fixed << std::setprecision(2);
      std::cout << "+ " << in << " - " << out << '\n';
    } else {
      for (int i = everything.now_size - count; i < everything.now_size; ++i) {
        if (everything.all_information[i] > 0) in += everything.all_information[i];
        if (everything.all_information[i] < 0) out += (-everything.all_information[i]);
      }
      std::cout << std::fixed << std::setprecision(2);
      std::cout << "+ " << in << " - " << out << '\n';
    }
    log_stream.close();
  }
};
#endif //BOOKSTORE_REAL__LOG_H_
