#include <mqueue.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  struct mq_attr attr;
  char buffer[2048]={0};
  int prio, numRead;
  mqd_t mqd;

  mqd = mq_open("/mq_flash", O_RDONLY | O_RDWR );
  mq_getattr(mqd, &attr);
  printf("%d %d\n",attr.mq_maxmsg,attr.mq_msgsize);

  numRead =  mq_receive(mqd, buffer, attr.mq_msgsize, &prio);
  printf("%s:%d\n",buffer, prio);

  numRead =  mq_receive(mqd, buffer, attr.mq_msgsize, &prio);
  printf("%s:%d\n",buffer,prio);
}

/* Output
10 2048
Hello:11
World:9
*/
