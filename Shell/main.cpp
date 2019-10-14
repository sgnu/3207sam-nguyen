#include "process.hpp"
#include "prompt.hpp"
#include "builtin.hpp"

using namespace std;

int main() {
  string input;
  while (input != "exit") {
    printPrompt();
    getline(cin, input);

    Command command = parseCommand(input);
    if (command.command == "exit") {
      exit(0);
    } else if (command.command == "cd") {
      if (command.args[1] != "") {
        if (changeDir(command.args[1]) != 0) {
          cerr << command.args[1] << " is not a directory" << endl;
        }
      } else {
        cerr << "Expected an argument" << endl;
      }
    } else if (command.command == "help") {
      printHelp();
    } else if (command.command == "clr") {
      clr();
    } else {
      pid_t myP = makeP(command);
    }
  }
}
