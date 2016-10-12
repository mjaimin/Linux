###sigwaitinfo
* sigwaitinfo() removes the signal from the set of pending signals and returns the signal number as its function result.
* If there are multiple pending signals, the lowest numbered signal will be selected.
* If no signal in the signal set is pending at the time of the call to sigwaitinfo(), the thread is suspended until one or more of the signals specified in the signal set become pending or until it is interrupted by an unblocked, caught signal.
* If more than one thread is using sigwaitinfo() to wait for the same signal, only one of these threads will return from this routine with the signal number, until a second signal of the same type is received.
* The signal will not cause a signal handler to be invoked.

