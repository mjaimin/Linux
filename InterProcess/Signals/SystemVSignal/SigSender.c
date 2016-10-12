// ./a.out pid signum 
// SIGINT = 2
#include <signal.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
  pid_t pid = atoi(argv[1]);
  int sig = atoi(argv[2]);

  printf("%d %d\n",pid, sig);
  kill(pid, sig);
}
