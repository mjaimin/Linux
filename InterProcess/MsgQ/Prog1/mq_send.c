#include <mqueue.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  mqd_t mqd;
  struct mq_attr attr;
  int numWriten;

  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 2048;

  mqd = mq_open("/mq_flash", O_CREAT | O_RDONLY | O_RDWR, 0666, &attr);

  numWriten = mq_send(mqd, "World", sizeof("World"),9);
  numWriten = mq_send(mqd, "Hello", sizeof("Hello"),11);
}
