#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

void printPrompt() {
  // Get PWD from environment variables
  string pwd = getenv("PWD");
  stringstream ss(pwd);
  string curDir;

  // Tokenize pwd to get current directory
  while (getline(ss, curDir, '/')) {
  }

  time_t t = time(0);
  tm* now = localtime(&t);

  cout << now->tm_hour << ":" << now->tm_min << " " << curDir << '/' << endl;
}