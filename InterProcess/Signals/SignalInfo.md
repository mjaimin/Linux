**sigset_t**


The ***sigset_t*** data type is used to represent a signal set.

There are two ways to initialize a signal set. You can initially specify it to be **empty with sigemptyset** and then add specified signals individually. Or you can specify it to be **full with sigfillset** and then delete specified signals individually.

**sigemptyset:**

This function initializes the signal set set to exclude all of the defined signals.

**sigfillset:**

This function initializes the signal set set to include all of the defined signals

**sigaddset:**

This function adds the signal signum to the signal set set

**sigdelset:**

This function removes the signal signum from the signal set set.

**sigismember:**

The sigismember function tests whether the signal signum is a member of the signal set set.


**sigprocmask:**

This function is used to fetch and/or change the signal mask of the calling thread.

*SIG_BLOCK* to block the signals in the set list

*SIG_UNBLOCK* to unblock the signals in the set list

*SIG_SETMASK* blocks the signals in the list, and unblocks the ones that aren't set in the list.


