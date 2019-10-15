#include <fcntl.h>
#include <unistd.h>
#include "parser.hpp"

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
      open(command.outRedir.c_str(), O_CREAT | O_WRONLY, S_IRWXU);
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
  int fd[2];
  pipe(fd);

  p1 = fork();

  if (p1 == 0) {
    // Child

    dup2(fd[1], STDOUT_FILENO);  // Dup stdout
    close(fd[0]);
    close(fd[1]);

    char *arr1[99];
    argsToCStr(commands[0], arr1);

    execvp(arr1[0], arr1);

    close(fd[0]);
  } else if (p1 > 0) {
    // Parent

    p2 = fork();

    if (p2 == 0) {
      // Child

      dup2(fd[0], STDIN_FILENO);
      close(fd[0]);
      close(fd[1]);

      char *arr2[99];
      argsToCStr(commands[1], arr2);
      execvp(arr2[0], arr2);
    } else if (p2 > 0) {
      // Parent

      int status;
      while (-1 == (waitpid(p1, &status, 0)))
        ;
    } else {
      cerr << "Fork failed" << endl;
    }

    close(fd[0]);
    close(fd[1]);
  } else {
    cerr << "Pipe failed" << endl;
  }
}

void makeParallel(vector<string> strings) {
  vector<int> pids;
  vector<Command> commands;
  vector<vector<Command> > piped;

  // Parse strings into commands / piped commands
  for (int i = 0; i < strings.size(); i++) {
    if (strings[i].find('|') != string::npos) {
      vector<string> tokens;
      vector<Command> commands;
      stringstream ss(strings[i]);
      string token;

      // Split input into tokens separated by |
      while (getline(ss, token, '|')) {
        tokens.push_back(token);
      }
      piped.push_back(parseInputs(tokens));
    } else {
      commands.push_back(parseInput(strings[i]));
    }
  }

  for (int i = 0; i < commands.size(); i++) {
    makeP(commands[i]);
  }

  for (int i = 0; i < piped.size(); i++) {
    makePPipe(piped[i]);
  }

  while (true) {
    int status;
    pid_t done = wait(&status);
    if (done == -1) {
      if (errno == ECHILD) break;  // no more child processes
    } else {
      if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        cerr << "pid " << done << " failed" << endl;
        exit(1);
      }
    }
  }
}
