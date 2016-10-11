#include <stdio.h>
#include <signal.h>

static void SignalAction ( int signum, siginfo_t *si, void *uctx)
{
    printf("Signal handled\n");
}

void InstallSignalHandler ( )
{
    struct sigaction sa;

    sa.sa_flags     = SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = &SignalAction;
    sigfillset(&sa.sa_mask);
    sigaction(SIGSEGV, &sa, NULL); // segmentation fault
    sigaction(SIGILL,  &sa, NULL); // illegal instruction
    sigaction(SIGPIPE, &sa, NULL);
    sigaction(SIGFPE,  &sa, NULL); // div0 and more
    sigaction(SIGABRT, &sa, NULL);
    sigaction(SIGINT,  &sa, NULL);
    sigaction(SIGBUS,  &sa, NULL);
}

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

int AllowSelectSignal( int sig )
{
  sigset_t sigset;
  sigemptyset(&sigset);
  sigaddset(&sigset,sig);
  //multiple signals can also be added to unblock
  //sigaddset(&sigset,SIGSEGV);  //sigaddset(&sigset,SIGPIPE);
  //sigaddset(&sigset,SIGABRT);
  //sigdelset(&sigset,SIGABRT);
  sigprocmask(SIG_UNBLOCK, &sigset , NULL);
}

int main()
{
  printf("%d\n",getpid());
  InstallSignalHandler();
  BlockAllSignals();
  AllowSelectSignal(SIGINT); // CTRL+C
  while(1)
      sleep(1);
}
