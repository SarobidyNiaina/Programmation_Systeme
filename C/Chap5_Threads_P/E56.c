#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define N 100

double tableau[N];
pthread_mutex_t mutex;

/* -------- Thread 1 : mise à jour -------- */
void* modifier(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);

        for(int i = 1; i < N-1; i++)
        {
            tableau[i] = (tableau[i-1] + tableau[i] + tableau[i+1]) / 3.0;
        }

        pthread_mutex_unlock(&mutex);

        sleep(rand() % 3 + 1); // 1 à 3 secondes
    }

    return NULL;
}

/* -------- Thread 2 : affichage -------- */
void* afficher(void* arg)
{
    while(1)
    {
        sleep(4);

        pthread_mutex_lock(&mutex);

        printf("Tableau :\n");
        for(int i = 0; i < N; i++)
        {
            printf("%.2f ", tableau[i]);
        }
        printf("\n\n");

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

/* -------- MAIN -------- */
int main()
{
    srand(time(NULL));

    pthread_t th1, th2;

    pthread_mutex_init(&mutex, NULL);

    /* Initialisation */
    tableau[0] = 0;
    tableau[N-1] = 0;

    for(int i = 1; i < N-1; i++)
    {
        tableau[i] = (double)(rand() % 100);
    }

    pthread_create(&th1, NULL, modifier, NULL);
    pthread_create(&th2, NULL, afficher, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
