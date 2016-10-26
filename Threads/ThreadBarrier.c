#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define THREAD_NUM 2

static pthread_barrier_t barrier;

void* thread(void *arg)
{
  pthread_barrier_wait(&barrier);
  printf("Thread barrier reached\n");
  pthread_exit(0);
  return NULL;
}

int main()
{
  int cnt;
  pthread_t child_threads[THREAD_NUM];

  pthread_barrier_init(&barrier, NULL, THREAD_NUM);

  for(cnt = 0; cnt < THREAD_NUM; cnt++)
  {
    pthread_create(&child_threads[cnt], NULL, thread, &cnt);
    sleep(4);
  }
  for(cnt = 0; cnt < THREAD_NUM; cnt++)
  {
    pthread_join(child_threads[cnt], NULL);
  }
  pthread_barrier_destroy(&barrier);
  return 0;
}
