#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
  int     fd[2], nbytes;
  pid_t   childpid;
  char    string[] = "Hello, world!\n";
  char    readbuffer[80];

  pipe(fd);

  childpid = fork();

  if(childpid == 0)
  {

    close(fd[0]); /* Child process closes up input side of pipe */

    write(fd[1], string, (strlen(string)+1));
    exit(0);
  }
  else
  {
    close(fd[1]); /* Parent process closes up output side of pipe */

    nbytes = read(fd[0], readbuffer, sizeof(readbuffer)); /* Read in a string from the pipe */

    printf("Received string: %s", readbuffer);
  }

  return(0);
}

