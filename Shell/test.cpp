#include "parser.hpp"
#include "prompt.hpp"

using namespace std;

int main() {
  cout << "Prompt:" << endl;
  printPrompt();
  cout << endl;

  cout << "Command Parser (cmd is 'ls -la'):" << endl;
  Command testCommand = parseCommand("ls -la");
  cout << testCommand.toString() << endl;
}