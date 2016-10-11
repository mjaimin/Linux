#include <stdio.h>
#include <signal.h>
#include <string.h>

void                    /* Print list of signals within a signal set */
printSigset( const sigset_t *sigset)
{
    int sig, cnt;
    cnt = 0;
    for (sig = 1; sig < NSIG; sig++) {
	if (sigismember(sigset, sig)) {
	    cnt++;
	    printf("%d (%s)\n", sig, strsignal(sig));
	}
    }
    if (cnt == 0)
	printf("empty signal set\n");
}

int                     /* Print mask of blocked signals for this process */
printSigMask(void)
{
    sigset_t currMask;

    sigprocmask(SIG_BLOCK, NULL, &currMask); 

    printSigset(&currMask);

    return 0;
}

int                     /* Print signals currently pending for this process */
printPendingSigs(void)
{
    sigset_t pendingSigs;

    sigpending(&pendingSigs);

    printSigset(&pendingSigs);
    return 0;
}
int main()
{

    sigset_t blocked, pending;

    /* Block SIGINT for a while */

    sigemptyset(&blocked);
    sigaddset(&blocked, SIGINT);
    sigaddset(&blocked, SIGBUS);
    sigaddset(&blocked, SIGPIPE);
    sigprocmask(SIG_SETMASK, &blocked, NULL);

    printf("---------Current Mask-----------\n");
    printSigMask();
    printf("--------Pending Signals---------\n");
    do
    {
	printPendingSigs();
	sleep(1);
    }while(1);
}
