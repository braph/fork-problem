#include <stdio.h>  // printf
#include <stdlib.h> // exit, atexit
#include <unistd.h> // fork, pipe

int main(int argc, char* const argv[])
{
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    perror("pipe()");
    return 1;
  }

  int pid = fork();
  switch (pid) {
  case -1:
    perror("fork()");
    return 1;
  case 0:
    close(pipefd[0]);
    /*
     * This would fix the problem, but then the child process cannot print anymore
     *
    close(0);
    close(1);
    close(2);
    */
    break;
  default:
    close(pipefd[1]);

    char buf;
    if (read(pipefd[0], &buf, 1) == 1)
      _exit(0);
    else
      _exit(3);
  }

  // Here goes some code that initializes the program
  if (0)
    return 1;

  // This code only runs if the initialization suceeded
  if (write(pipefd[1], "1", 1) == -1) {
    perror("write()");
    return 1;
  }
  close(pipefd[1]); 

  while (1) {
    printf("Living...\n");
    sleep(1);
  }

  return 0;
}

