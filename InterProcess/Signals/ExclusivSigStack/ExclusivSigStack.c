#include <string.h>
#include <signal.h>
#include <stdio.h>

/*A signal stack is a special area of memory to be used as the execution stack during signal handlers. It should be fairly large, to avoid any danger that it will overflow in turn; the macro SIGSTKSZ is defined to a canonical size for signal stacks. You can use malloc to allocate the space for the stack. Then call sigaltstack or sigstack to tell the system to use that space for the signal stack.

You don’t need to write signal handlers differently in order to use a signal stack. Switching from one stack to the other happens automatically. (Some non-GNU debuggers on some machines may get confused if you examine a stack trace while a handler that uses the signal stack is running.)*/

static void sigsegvHandler(int sig)
{
    int x;

    /* UNSAFE: This handler uses non-async-signal-safe functions
     *        (printf(), strsignal(), fflush(); see Section 21.1.2) */

    printf("Caught signal %d (%s)\n", sig, strsignal(sig));
    printf("Top of handler stack near     %10p\n", (void *) &x);
    fflush(NULL);
}

int main(int argc, char *argv[])
{
    stack_t sigstack;
    struct sigaction sa;
    int j;

    printf("Top of standard stack is near %10p\n", (void *) &j);

    /* Allocate alternate stack and inform kernel of its existence */
/*    SIGSTKSZ
	[XSI] [Option Start] Default size in bytes for the alternate signal stack. [Option End]*/

    sigstack.ss_sp =(void*) malloc(SIGSTKSZ);

    sigstack.ss_size = SIGSTKSZ;
    sigstack.ss_flags = 0;
    sigaltstack(&sigstack, NULL) ;
    printf("Alternate stack is at         %10p-%p\n", sigstack.ss_sp, (char *) sbrk(0) - 1);

    sa.sa_handler = sigsegvHandler;     /* Establish handler for SIGSEGV */
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_ONSTACK;           /* Handler uses alternate stack */
    sigaction(SIGSEGV, &sa, NULL);
}
