#ifndef BOOKSTORE_REAL__ACCOUNT_H_
#define BOOKSTORE_REAL__ACCOUNT_H_
#include <unordered_set>
#include "ErrorException.h"
#include "book.h"

/*------------------------Account Part----------------------------
 * this part mainly deal with the accounts of users, and check the
 * validity of the initializing information
 * -------------------------------------------------------------*/

const int MaxLen = 30;
const int PrivilegeLen = 1;
const std::unordered_set<std::string> Privilege = {"0", "1", "3", "7"};
// all the possible privilege

// check the validity of name
bool UserNameCheck(const std::string &_name) {
  if (_name.length() > MaxLen) return false;
  for (int i = 0; i < _name.length(); ++i) {
    if (_name[i] < 33 || _name[i] == 127) return false;
  }
  return true;
}

// check the validity of other information
// including passwords and IDs
bool UserInfoCheck(const std::string &_info) {
  if (_info.length() > MaxLen) return false;
  for (int i = 0; i < _info.length(); ++i) {
    if (!(_info[i] == '_' || _info[i] <= '9' && _info[i] >= '0' ||
        _info[i] <= 'z' && _info[i] >= 'a' || _info[i] <= 'Z' && _info[i] >= 'A'))
      return false;
  }
  return true;
}

// check the validity of privilege
bool PrivilegeCheck(const std::string &_privilege) {
  if (_privilege.length() != PrivilegeLen) return false;
  else if (_privilege[0] < 48 || _privilege[0] > 57) return false;
  else if (Privilege.find(_privilege) == Privilege.end()) return false;
  return true;
}

/* ---------------------------class user-----------------------------
 * store the information of one account, and the operations
 * -----------------------------------------------------------------*/

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
      const std::string &_Username = "") {
    if (!UserInfoCheck(_UserID) || !UserNameCheck(_Username) || !UserInfoCheck(_Password)
        || !PrivilegeCheck(_privilege)) {
      throw ErrorException();
    }
    strcpy(UserID, _UserID.c_str());
    strcpy(Password, _Password.c_str());
    strcpy(Username, _Username.c_str());
    privilege = _privilege[0] - 48;
  }
  void ChangePassword(const std::string &new_password) {
    memset(Password, 0, sizeof(Password));
    strcpy(Password, new_password.c_str());
  }
  friend bool operator<(const User &cmp_1, const User &cmp_2) {
    return (std::string) cmp_1.UserID < (std::string) cmp_2.UserID;
  }
  friend bool operator==(const User &cmp_1, const User &cmp_2) {
    return (std::string) cmp_1.UserID == (std::string) cmp_2.UserID;
  }
  User &operator=(const User &cmp) {
    if (&cmp == this) return *this;
    else {
      memset(Password, 0, sizeof(Password));
      memset(UserID, 0, sizeof(UserID));
      memset(Username, 0, sizeof(Username));
      strcpy(Password, cmp.Password);
      strcpy(UserID, cmp.UserID);
      strcpy(Username, cmp.Username);
      privilege = cmp.privilege;
      selected = cmp.selected;
      choosing = cmp.choosing;
      return *this;
    }
  }
  friend bool operator!=(const User &cmp_1, const User &cmp_2) {
    return (std::string) cmp_1.UserID != (std::string) cmp_2.UserID;
  }
  friend std::ostream &operator<<(std::ostream &os, const User &out) {
    os << out.UserID << " " << out.Password << " " << out.privilege << " " << out.Username << '\n';
    return os;
  }
};

#endif //BOOKSTORE_REAL__ACCOUNT_H_
