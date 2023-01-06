#include <iostream>
#include <string>
#include <vector>
#include "explain.h"
#include "program.h"
using namespace std;

string operation;
int main() {
   freopen("2.in","r",stdin);
   freopen("out.txt","w",stdout);
  ios::sync_with_stdio(false);
  Program myProgram;
  while (getline(cin,operation)) {
    try {
      //----1----
      //check the grammar validity
      std::cout << operation << '\n';
      if (operation.length() > 1024) throw ErrorException();
      std::vector<std::string> todo = Decompose(operation);
      if (todo.size() == 1 && (todo[0] == "exit" || todo[0] == "quit")) {
        return 0;
      }
      //----2----
      //run the operations
      Execute(myProgram,todo);
    } catch (ErrorException) {
      //----3----
      //in case of wrong messages
      cout <<"Invalid" << '\n';
    }
  }
  return 0;
}
