#include "builtin.hpp"
#include "process.hpp"
#include "prompt.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  string input;
  if (argc > 1) {
    // Runs an external file
    cout << "hello" << endl;
  } else {
    // Runs an interactive shell
    while (input != "exit") {
      printPrompt();
      getline(cin, input);

      if (input.find('|') != string::npos) {
        vector<string> inputs;
        stringstream ss(input);
        string token;

        // Split input into tokens separated by |
        while (getline(ss, token, '|')) {
          inputs.push_back(token);
        }
        
        vector<Command> commands = parseInputs(inputs);
      }

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
      } else if (command.command == "dir") {
        //
      } else if (command.command == "echo") {
        for (int i = 1; i < command.args.size(); i++) {
          cout << command.args[i] << " ";
        }
        cout << endl;
      } else {
        pid_t myP = makeP(command);
      }
    }
  }
}
