#include <signal.h>
#include <stdio.h>

void sigHandler(int sig)
{
  printf("Ouch!\n");
}

int main(int argc, char *argv[])
{
  if (signal(SIGINT, sigHandler) == SIG_ERR)
    exit(-1);

  while(1) {
    sleep(3);
  }
}
