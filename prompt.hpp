#include <iostream>
#include <stdio.h>
#include <sstream>

using namespace std;

void printPrompt() {
  string pwd = getenv("PWD");
  stringstream ss(pwd);
  string curDir;
  while (getline(ss, curDir, '/')) {}

  cout << curDir << endl;
}