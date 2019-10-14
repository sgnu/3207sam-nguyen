// #include "parser.hpp"
#include "process.hpp"
#include "prompt.hpp"

using namespace std;

int main() {
  Command testCommand = parseCommand("ls /bin > build/log");

  cout << "Prompt:" << endl;
  printPrompt();
  cout << endl;

  cout << "---------------------------------" << endl;

  cout << "Command Parser (cmd is 'ls /bin > build/log'):" << endl;
  cout << "Command: " << testCommand.getCommand() << endl;
  cout << "Args:" << testCommand.getArgs() << endl;
  cout << "In: " << testCommand.inRedir << endl;
  cout << "Out: " << testCommand.outRedir << endl;

  cout << "---------------------------------" << endl;

  cout << "Execution (cmd is 'ls /bin > build/log'):" << endl;
  pid_t myP = makeP(testCommand);
}