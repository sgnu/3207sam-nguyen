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
        changeDir(command.args[1]);
      } else {
        cerr << "Expected an argument" << endl;
      }
    } else if (command.command == "help") {
      printHelp();
    } else {
      pid_t myP = makeP(command);
    }
  }
}
