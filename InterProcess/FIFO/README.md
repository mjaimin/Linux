Normally, blocking occurs on a FIFO. In other words, if the FIFO is opened for reading,
the process will "block" until some other process opens it for writing. This action works
vice-versa as well. If this behavior is undesirable, the O_NONBLOCK flag can be used in
an open() call to disable the default blocking action. 
