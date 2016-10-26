#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
void cleanup(void *m)
{
  pthread_mutex_unlock(m);
  printf("Used for releasing any type of possibly open HANDLE\n");
  printf("Usage during:\n");
  printf("pthread exit\n");
  printf("pthread cancel\n");
}

void innerFunction()
{
  pthread_cleanup_push (cleanup, &mutex1 );
  pthread_mutex_lock( &mutex1 );
  sleep(1000);
  pthread_mutex_unlock( &mutex1 );
  pthread_cleanup_pop (0);
}
void *functionA()
{
  pthread_cleanup_push (cleanup, &mutex2 );
  pthread_mutex_lock( &mutex2 );
  innerFunction();
  pthread_mutex_unlock( &mutex2 );
  return NULL;
  pthread_cleanup_pop (0);
}

int main()
{
  pthread_t tID;
  pthread_create( &tID, NULL, &functionA, NULL);
  pthread_cancel(tID);
  pthread_join( tID, NULL);
}
