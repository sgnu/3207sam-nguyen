#include <fcntl.h>
#include "parser.hpp"
#include <unistd.h>

/**
 * Takes a Command and creates a new process that executes it
 */
pid_t makeP(Command command) {
  pid_t newP = fork();
  if (newP == 0) {
    // Child process

    char *arr[99];
    argsToCStr(command, arr);

    if (!command.outRedir.empty()) {
      close(STDOUT_FILENO);
      open(command.outRedir.c_str(), O_CREAT|O_WRONLY, S_IRWXU);
    }

    // execvp checks the PATH for us
    // exec family returns -1 when there is an error
    if (execvp(command.command.c_str(), arr) < 0) {
      // Error is most likely that
      cerr << command.command << " is not a recognized command" << endl;
      exit(0);
    }
  } else if (newP > 0) {
    // Parent process
    wait(NULL);
  } else {
    // Error in forking
    cerr << "Fork failed" << endl;
  }

  return newP;
}