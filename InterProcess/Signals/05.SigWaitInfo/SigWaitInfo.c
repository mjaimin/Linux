#include <string.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
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
    sigaction(SIGINT,  &sa, NULL);
}

int main(int argc, char *argv[])
{
    int sig;
    siginfo_t si;
    sigset_t allSigs;

    InstallSignalHandler();
    sigfillset(&allSigs);
    sigprocmask(SIG_UNBLOCK, &allSigs, NULL);
    //1. sigwaitinfo() removes the signal from the set of pending signals and returns the signal number as its function result.
    //2. If there are multiple pending signals, the lowest numbered signal will be selected.
    //3. If no signal in the signal set is pending at the time of the call to sigwaitinfo(), the thread is suspended until one or more of the signals specified in the signal set become pending or until it is interrupted by an unblocked, caught signal.
    //4. If more than one thread is using sigwaitinfo() to wait for the same signal, only one of these threads will return from this routine with the signal number, until a second signal of the same type is received.
    //5. The signal will not cause a signal handler to be invoked.
    printf("Before sigwaitinfo\n");
    sig = sigwaitinfo(&allSigs, &si);

    if (sig == SIGINT || sig == SIGTERM)
	printf("Proceed to branch\n");

    printf("After sigwaitinfo\n");
}
