#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

enum redirect {
  NONE,
  PIPE,
  INPUT,
  OUTPUT
};

class Command {
  public:
    string command;
    vector<string> args;
    redirect rd;

    void setCommand(string command);
    void setArgs(vector<string> args);
};

void Command::setCommand(string command) {
  this->command = command;
}

void Command::setArgs(vector<string> args) {
  this->args = args;
}

Command parseCommand(string input) {
  stringstream ss(input);
  string token;
  vector<string> tokens;

  Command command;

  while (getline(ss, token, ' ')) {
    tokens.push_back(token);
  }

  command.setCommand(tokens.at(0));

  return command;
}

Command parseInput(string input) {
  stringstream ss(input);
  string token;
  Command command = parseCommand(input);

  return command;
}
