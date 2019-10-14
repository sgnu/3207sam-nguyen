#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Command {
 public:
  string command;
  vector<string> args;
  // File descriptor if command is input redir
  string inRedir;
  // File descriptor if command is output redir
  string outRedir;

  void setCommand(string command) { this->command = command; }
  void setArgs(vector<string> args) { this->args = args; }
  void setIn(string path) { this->inRedir = path; }
  void setOut(string path) { this->outRedir = path; }

  /**
   * @returns the command and all arguments
   */
  string toString() {
    string retval = command;

    for (vector<string>::iterator it = this->args.begin();
         it != this->args.end(); ++it) {
      retval += " " + *it;
    }

    return retval;
  }

  /**
   * @returns the command
   */
  string getCommand() { return this->command; }

  /**
   * @returns all arguments
   */
  string getArgs() {
    string retval = "";

    for (vector<string>::iterator it = this->args.begin();
         it != this->args.end(); ++it) {
      retval += " " + *it;
    }

    return retval;
  }
};

/**
 * Parses a string into a Command
 */
Command parseCommand(string input) {
  stringstream ss(input);
  string token;
  vector<string> tokens;

  Command command;

  while (getline(ss, token, ' ')) {
    if (token == "<") {
      getline(ss, token, ' ');
      command.setIn(token);
    } else if (token == ">") {
      getline(ss, token, ' ');
      command.setOut(token);
    } else {
      tokens.push_back(token);
    }
  }

  command.setCommand(tokens.at(0));
  command.setArgs(tokens);

  return command;
}

/**
 * Parses an input into a Command (will be reworked into a vector of commands)
 */
Command parseInput(string input) { return parseCommand(input); }

/**
 * Parses inputs into separate commands
 * @param input Vector of strings to convert
 * @returns Vector of Commands
 */
vector<Command> parseInputs(vector<string> input) {
  vector<Command> commands;
  for (vector<string>::iterator it = input.begin(); it != input.end(); ++it) {
    commands.push_back(parseCommand(*it));
  }
  return commands;
}

/**
 * @param command command to get args from
 * @param cArgs array to be copied to;
 */
void argsToCStr(Command command, char **cArgs) {
  int i;
  for (i = 0; i < command.args.size(); i++) {
    cArgs[i] = (char *)malloc(800);
    const char *mystring = command.args[i].c_str();
    strcpy(cArgs[i], mystring);
  }
  cout << i;
  cArgs[i] = nullptr;
}