#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> parseInput(string input) {
  stringstream ss(input);
  string token;
  vector<string> tokens;

  while (getline(ss, input, ' ')) {
    tokens.push_back(token);
  }

  return tokens;
}

class Command {
  public:
    string command;
    vector<string> args;
};