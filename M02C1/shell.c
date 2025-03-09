#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_TOKENS 64

int main() {
  printf("Welcome to the most basic shell program ever!\n");

  // while loop to get input
  while (1) {
    // prompt, prints the cwd
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("%s$ ", cwd);
    } else {
      printf("$ ");
    }
    fflush(stdout);

    // get user input
    char *input = NULL;
    size_t len = 0;
    ssize_t nread = getline(&input, &len, stdin);
    if (nread == -1) {
      free(input);
      break;
    }

    // drop the newline
    if (input[nread - 1] == '\n') {
      input[nread - 1] = '\0';
    }

    // split by spaces/tabs
    char *tokens[MAX_TOKENS];
    int pos = 0;
    char *token = strtok(input, " \t");
    while (token && pos < MAX_TOKENS - 1) {
      tokens[pos++] = token;
      token = strtok(NULL, " \t");
    }
    tokens[pos] = NULL;

    // if no input, free and restart loop
    if (tokens[0] == NULL) {
      free(input);
      continue;
    }

    // built-in command: cd
    if (strcmp(tokens[0], "cd") == 0) {
      if (tokens[1] != NULL) {
        chdir(tokens[1]);
      }
      free(input);
      continue;
    }

    // built-in command: quit
    if (strcmp(tokens[0], "quit") == 0) {
      free(input);
      break;
    }

    // for external commands, fork a child and execvp
    pid_t pid = fork();
    if (pid == 0) {
      // child: run command
      execvp(tokens[0], tokens);
      exit(1);
    } else if (pid > 0) {
      // parent: wait for child to finish
      wait(NULL);
    }

    // free the input buffer before next loop
    free(input);
  }
  return 0;
}
