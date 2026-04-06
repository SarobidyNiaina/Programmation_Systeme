#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

/* variable partagée */
char buffer;

/* sémaphores */
sem_t vide;
sem_t plein;

void* emetteur(void* arg)
{
    while(1)
    {
        sleep(rand() % 3 + 1);

        char c = 'A' + rand() % 26;

        sem_wait(&vide);  // attendre que ce soit vide

        buffer = c;
        printf("[EMETTEUR] envoie : %c\n", c);

        sem_post(&plein); // signaler que c'est plein
    }

    return NULL;
}

void* recepteur(void* arg)
{
    while(1)
    {
        sleep(rand() % 3 + 1);

        sem_wait(&plein); // attendre qu'il y ait un message

        char c = buffer;
        printf("          [RECEPTEUR] reçoit : %c\n", c);

        sem_post(&vide);  // libérer la case
    }

    return NULL;
}

int main()
{
    srand(time(NULL));

    pthread_t t1, t2;

    sem_init(&vide, 0, 1);  // 1 case libre
    sem_init(&plein, 0, 0); // rien au début

    pthread_create(&t1, NULL, emetteur, NULL);
    pthread_create(&t2, NULL, recepteur, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&vide);
    sem_destroy(&plein);

    return 0;
}
