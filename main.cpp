#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
#include "explain.h"
#include "program.h"
using namespace std;

string operation;
using std::cout;
int main() {
  //freopen("testcase4.in","r",stdin);
  //freopen("out.txt","w",stdout);
  ios::sync_with_stdio(false);
  //cin.tie(nullptr);
  //cout.tie(nullptr);
  Program myProgram;
  while (getline(cin,operation)) {
    //cout<<operation<<'\n';
    try {
      std::vector<std::string> todo = Decompose(operation);
      Execute(myProgram,todo);
    } catch (ErrorException) {
      cout <<"Invalid" << '\n';
    }
  }
  return 0;
}
