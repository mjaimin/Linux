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

void UninstallSignalHandler ( )
{
    struct sigaction sa;
    sa.sa_handler = SIG_DFL;
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGILL,  &sa, NULL);
    sigaction(SIGPIPE, &sa, NULL);
    sigaction(SIGFPE,  &sa, NULL);
    sigaction(SIGABRT, &sa, NULL);
    sigaction(SIGINT,  &sa, NULL);
    sigaction(SIGBUS,  &sa, NULL);
}

int main()
{
    printf("%d\n",getpid());
    InstallSignalHandler();
    while(1)
    {
	sleep(1);
    }
    UninstallSignalHandler();
}

