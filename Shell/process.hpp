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

    // Output redirect
    if (!command.outRedir.empty()) {
      close(STDOUT_FILENO);
      open(command.outRedir.c_str(), O_CREAT|O_WRONLY, S_IRWXU);
    }

    // Input redirect
    if (!command.inRedir.empty()) {
      close(STDIN_FILENO);
      open(command.inRedir.c_str(), O_RDONLY, S_IRWXU);
    }

    // execvp checks the PATH for us
    // exec family returns -1 when there is an error
    if (execvp(arr[0], arr) < 0) {
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

void makePPipe(vector<Command> commands) {
  pid_t p1, p2;
  // FDs
  int fd1[2], fd2[2];

  // Pipe for process 1 and 2
  if (pipe(fd1) == -1) {
    cerr << "Pipe failed" << endl;
  }
  if (pipe(fd2) == -1) {
    cerr << "Pipe failed" << endl;
  }

  p1 = fork();
  if (p1 == 0) {
    // Child
    int status;
    close(fd1[1]); // Close write end of pipe 1

    char *arr1[99];
    argsToCStr(commands[0], arr1);

    execvp(arr1[0], arr1);

    // Wait for process 1 to finish
    while (-1 == (waitpid(p1, &status, 0)));
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
      cerr << "Process failed" << endl;
      exit(1);
    }

    p2 = fork();
    if (p2 == 0) {
      // Child
      close(fd2[0]); // Close read end of pipe 2

      char *arr2[99];
      argsToCStr(commands[1], arr2);
      execvp(arr2[0], arr2);
    } else if (p2 > 0) {
      // Parent
    } else {
      cerr << "Fork failed" << endl;
    }
  } else if (p1 > 0) {
    // Parent
    close (fd1[0]); // Close read end of pipe 1

  } else {
    cerr << "Pipe failed" << endl;
  }
}