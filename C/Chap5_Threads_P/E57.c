#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int compt = 0;
double u = 1.0;

pthread_mutex_t mutex;

void* thread1(void* arg)
{
    while(1)
    {
        sleep(rand() % 5 + 1);

        pthread_mutex_lock(&mutex);

        compt++;

        u = (u - 1) * (u - 1) / 4.0;

        printf("[T1] iteration %d, u = %.5f\n", compt, u);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void* thread2(void* arg)
{
    while(1)
    {
        sleep(rand() % 5 + 1);

        pthread_mutex_lock(&mutex);

        compt++;

        u = (u - 2) * (u - 2) / 6.0;

        printf("[T2] iteration %d, u = %.5f\n", compt, u);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}
int main()
{
    srand(time(NULL));

    pthread_t t1, t2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
