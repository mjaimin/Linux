##Atomic Operations with Pipes##

In order for an operation to be considered 'atomic', it must not be interrupted for any reason at all. The entire operation occurs at once. According to POSIX standard the maximum buffer size for an atomic operation on a pipe is:

        #define _POSIX_PIPE_BUF         512  /// defined under /usr/include/posix1_lim.h

Up to 512 bytes can be written or retrieved from a pipe atomically. Anything that crosses this threshold will be split, and not atomic. 

But, Under Linux, however, the atomic operational limit is defined in 'linux/limits.h' as:

        #define PIPE_BUF        4096
