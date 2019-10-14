#include <iostream>
#include <unistd.h>

using namespace std;

void changeDir(string input) {
  chdir(input.c_str());
}

void printHelp() {
  cout << "help" << endl;
}