#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

int N;
int count = 0;

pthread_mutex_t mutex;
sem_t barrier;

void* travail(void* arg)
{
    int id = *(int*)arg;

    int t = rand() % 5 + 1;
    printf("Thread %d travaille (%d sec)\n", id, t);
    sleep(t);

    pthread_mutex_lock(&mutex);

    count++;

    if(count == N)
    {
        for(int i = 0; i < N; i++)
            sem_post(&barrier);
    }

    pthread_mutex_unlock(&mutex);

    sem_wait(&barrier);

    printf("Thread %d passe le rendez-vous\n", id);

    return NULL;
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s N\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);

    pthread_t threads[N];
    int ids[N];

    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);
    sem_init(&barrier, 0, 0);

    for(int i = 0; i < N; i++)
    {
        ids[i] = i;
        pthread_create(&threads[i], NULL, travail, &ids[i]);
    }

    for(int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&barrier);

    return 0;
}
