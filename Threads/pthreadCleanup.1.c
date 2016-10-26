#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void cleanup(void *m)
{
  pthread_mutex_unlock(m);
  printf("Used for releasing any type of possibly open HANDLE\n");
  printf("Usage during:\n");
  printf("pthread exit\n");
  printf("pthread cancel\n");
}

void *functionA()
{
  pthread_cleanup_push (cleanup, &mutex );
  pthread_mutex_lock( &mutex );
  sleep(1000);
  pthread_mutex_unlock( &mutex );
  return NULL;
  pthread_cleanup_pop (0);
}
void *functionB()
{
  pthread_cleanup_push (cleanup, &mutex );
  pthread_mutex_lock( &mutex );
  pthread_exit((void*)1);
  //return NULL; will not call cleanup
  pthread_mutex_unlock( &mutex );
  return NULL;
  pthread_cleanup_pop (0);
}

int main()
{
  pthread_t tID;
  pthread_create( &tID, NULL, &functionA, NULL);
  pthread_cancel(tID);
  pthread_join( tID, NULL);

  pthread_create( &tID, NULL, &functionB, NULL);
  pthread_join( tID, NULL);
}
