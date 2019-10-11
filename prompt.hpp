#include <iostream>
#include <stdio.h>

using namespace std;

void printPrompt() {
  char* pwd = getenv("PWD");

  cout << pwd;
}