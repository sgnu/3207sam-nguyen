#include <iostream>
#include <unistd.h>

using namespace std;

int changeDir(string input) {
  return chdir(input.c_str());
}

void printHelp() {
  cout << "myshell is an interactive shell that can run commands" << endl;
}

void clr() {
  cout << string(50, '\n');
}
