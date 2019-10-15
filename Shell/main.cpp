#include <fstream>
#include <iostream>
#include "builtin.hpp"
#include "process.hpp"
#include "prompt.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  string input;
  if (argc > 1) {
    ifstream myfile;
    myfile.open(argv[1], ios::in);
    while (getline(myfile, input)) {
      if (input.find('&') != string::npos) {
        vector<string> strings;
        stringstream ss(input);
        string token;

        while (getline(ss, token, '&')) {
          strings.push_back(token);
        }

        makeParallel(strings);
      } else if (input.find('|') != string::npos) {
        vector<string> tokens;
        vector<Command> commands;
        stringstream ss(input);
        string token;

        // Split input into tokens separated by |
        while (getline(ss, token, '|')) {
          tokens.push_back(token);
        }

        commands = parseInputs(tokens);

        makePPipe(commands);
      } else {
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
          makeP(command);
        }
      }
    }
    myfile.close();
  } else {
    // Runs an interactive shell
    printPrompt();
    getline(cin, input);

    do {
      if (input.find('&') != string::npos) {
        vector<string> strings;
        stringstream ss(input);
        string token;

        while (getline(ss, token, '&')) {
          strings.push_back(token);
        }

        makeParallel(strings);
      } else if (input.find('|') != string::npos) {
        vector<string> tokens;
        vector<Command> commands;
        stringstream ss(input);
        string token;

        // Split input into tokens separated by |
        while (getline(ss, token, '|')) {
          tokens.push_back(token);
        }

        commands = parseInputs(tokens);

        makePPipe(commands);
      } else {
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
          makeP(command);
        }
      }
      if (argc == 1) {
        printPrompt();
        getline(cin, input);
      }

    } while (input != "exit");
  }
}
