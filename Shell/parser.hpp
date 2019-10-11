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

    void setCommand(string command) {
      this->command = command;
    }

    void setArgs(vector<string> args) {
      this->args = args;
    }

    string toString() {
      string retval = command;

      for (vector<string>::iterator it = this->args.begin(); it != this->args.end(); ++it) {
        retval += " " + *it;
      }

      return retval;
    }
};


Command parseCommand(string input) {
  stringstream ss(input);
  string token;
  vector<string> tokens;

  Command command;

  while (getline(ss, token, ' ')) {
    tokens.push_back(token);
  }

  command.setCommand(tokens.at(0));
  tokens.erase(tokens.begin());
  command.setArgs(tokens);

  return command;
}

Command parseInput(string input) {
  stringstream ss(input);
  string token;
  Command command = parseCommand(input);

  return command;
}
