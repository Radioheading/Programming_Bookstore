#include <iostream>
#include <string>
#include <vector>
#include "explain.h"
#include "program.h"
using namespace std;

string operation;
using std::cout;
int main() {
  //freopen("1.in","r",stdin);
  ios::sync_with_stdio(false);
  //cin.tie(nullptr);
  //cout.tie(nullptr);
  Program myProgram;
  while (getline(cin,operation)) {
    try {
      //cout<<operation<<'\n';
      //----1----
      //check the grammar validity
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
