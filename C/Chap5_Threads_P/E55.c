#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

/* compteur global */
int compt = 0;
int limite;

pthread_mutex_t mutex;


void* incrementer(void* arg)
{
    while(1)
    {
        sleep(rand() % 5 + 1); // 1 à 5 secondes

        pthread_mutex_lock(&mutex);

        if(compt >= limite)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }

        compt++;
        printf("[INC] compt = %d\n", compt);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void* afficher(void* arg)
{
    while(1)
    {
        sleep(2);

        pthread_mutex_lock(&mutex);

        if(compt >= limite)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }

        printf("[AFF] compt = %d\n", compt);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

/* -------- MAIN -------- */
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s <limite>\n", argv[0]);
        return 1;
    }

    limite = atoi(argv[1]);

    srand(time(NULL));

    pthread_t th1, th2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&th1, NULL, incrementer, NULL);
    pthread_create(&th2, NULL, afficher, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("Fin du programme. compt = %d\n", compt);

    return 0;
}
