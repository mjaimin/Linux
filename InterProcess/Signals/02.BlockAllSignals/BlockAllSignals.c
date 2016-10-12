#include <stdio.h>
#include <signal.h>

void BlockAllSignals (void)
{
  sigset_t sigset;
  sigfillset(&sigset);
  sigprocmask(SIG_SETMASK, &sigset , NULL);
}

void UnblockAllSignals (void)
{
  sigset_t sigset;
  sigemptyset(&sigset);
  sigprocmask(SIG_SETMASK, &sigset , NULL);
}

int main()
{
  printf("%d\n",getpid());
  BlockAllSignals();
  while(1)
  {
    sleep(1);
  }
  UnblockAllSignals();
}
