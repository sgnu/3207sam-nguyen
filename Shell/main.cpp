#include "process.hpp"
#include "prompt.hpp"

using namespace std;

int main() {
  string input;
  while (input != "exit") {
    printPrompt();
    getline(cin, input);

    Command command = parseCommand(input);
    pid_t myP = makeP(command);
  }
  exit(0);
}
