#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

sem_t sem1, sem2;

void* T1(void* arg)
{
    for(int i = 0; i < 10; i++)
    {
        printf("T1 travaille...\n");
        sleep(2);

        printf("T1 attend T2\n");

        sem_post(&sem1); // je suis prêt
        sem_wait(&sem2); // j'attends T2

        printf("T1 repart\n\n");
    }
    return NULL;
}

void* T2(void* arg)
{
    for(int i = 0; i < 10; i++)
    {
        int t = rand() % 6 + 4; // 4 à 9 sec

        printf("T2 travaille (%d sec)...\n", t);
        sleep(t);

        printf("T2 attend T1\n");

        sem_post(&sem2); // je suis prêt
        sem_wait(&sem1); // j'attends T1

        printf("T2 repart\n\n");
    }
    return NULL;
}


int main()
{
    srand(time(NULL));

    pthread_t t1, t2;

    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);

    pthread_create(&t1, NULL, T1, NULL);
    pthread_create(&t2, NULL, T2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}
