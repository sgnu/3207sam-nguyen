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
    // File descriptor if command is input redir
    int inRedir;
    // File descriptor if command is output redir
    int outRedir;

    void setCommand(string command) {
      this->command = command;
    }

    void setArgs(vector<string> args) {
      this->args = args;
    }

    // Returns the full string of command and args
    string toString() {
      string retval = command;

      for (vector<string>::iterator it = this->args.begin(); it != this->args.end(); ++it) {
        retval += " " + *it;
      }

      return retval;
    }

    // Returns the command
    string getCommand() {
      return this->command;
    }

    // Returns the args
    string getArgs() {
      string retval = "";

      for (vector<string>::iterator it = this->args.begin(); it != this->args.end(); ++it) {
        retval += " " + *it;
      }

      return retval;
    }
};

// Parses a given input into a Command
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

// Parses an input into a Command (will be reworked into a vector of commands)
Command parseInput(string input) {
  stringstream ss(input);
  string token;
  Command command = parseCommand(input);

  return command;
}
