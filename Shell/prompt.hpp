#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

void printPrompt() {
  // // Get PWD from environment variables
  // string pwd = getenv("PWD");
  // stringstream ss(pwd);
  // string curDir;

  // // Tokenize pwd to get current directory
  // while (getline(ss, curDir, '/')) {
  // }

  // // Get current time
  // time_t t = time(0);
  // tm* now = localtime(&t);

  // // Prints time as HH:MM (24 hour format)
  // cout << now->tm_hour << ":" << now->tm_min << " /" << curDir << '/' << endl;
  cout << "\033[36m" << "myshell> " << "\033[0m";
}
