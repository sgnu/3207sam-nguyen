#include "parser.hpp"
#include "prompt.hpp"

using namespace std;

int main() {
  cout << "Prompt:" << endl;
  printPrompt();
  cout << endl;

  cout << "Command Parser (cmd is 'ls -la > /tmp/log'):" << endl;
  Command testCommand = parseCommand("ls -la > /tmp/log");
  cout << "Command: " << testCommand.getCommand() << endl;
  cout << "Args: " << testCommand.getArgs() << endl;
  cout << "In: " << testCommand.inRedir << endl;
  cout << "Out: " << testCommand.outRedir << endl;
}