#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    int* tab;
    int taille;
} Tableau;

/* ---------- Génération aléatoire ---------- */
void* generer(void* arg)
{
    Tableau* t = (Tableau*) arg;

    for(int i = 0; i < t->taille; i++)
    {
        t->tab[i] = rand() % 100;
    }

    return NULL;
}

/* ---------- Vérifier inclusion ---------- */
void* inclusion(void* arg)
{
    Tableau* t = (Tableau*) arg;

    int* T1 = t[0].tab;
    int n1 = t[0].taille;

    int* T2 = t[1].tab;
    int n2 = t[1].taille;

    for(int i = 0; i < n1; i++)
    {
        int trouve = 0;

        for(int j = 0; j < n2; j++)
        {
            if(T1[i] == T2[j])
            {
                trouve = 1;
                break;
            }
        }

        if(!trouve)
        {
            printf("T1 n'est PAS inclus dans T2\n");
            return NULL;
        }
    }

    printf("T1 est inclus dans T2\n");
    return NULL;
}

/* ---------- Annulation ---------- */
void* annulation(void* arg)
{
    char c;

    while(1)
    {
        scanf(" %c", &c);

        if(c == 'A')
        {
            printf("Programme annulé par l'utilisateur\n");
            exit(0);
        }
    }
}

/* ---------- MAIN ---------- */
int main()
{
    srand(time(NULL));

    pthread_t th1, th2, th3, th_cancel;

    /* tailles */
    int n1 = 5;
    int n2 = 10;

    /* allocation */
    Tableau T[2];

    T[0].taille = n1;
    T[0].tab = malloc(n1 * sizeof(int));

    T[1].taille = n2;
    T[1].tab = malloc(n2 * sizeof(int));

    /* thread annulation */
    pthread_create(&th_cancel, NULL, annulation, NULL);

    /* génération parallèle */
    pthread_create(&th1, NULL, generer, &T[0]);
    pthread_create(&th2, NULL, generer, &T[1]);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    /* affichage */
    printf("T1: ");
    for(int i = 0; i < n1; i++) printf("%d ", T[0].tab[i]);
    printf("\n");

    printf("T2: ");
    for(int i = 0; i < n2; i++) printf("%d ", T[1].tab[i]);
    printf("\n");

    /* inclusion */
    pthread_create(&th3, NULL, inclusion, T);
    pthread_join(th3, NULL);

    free(T[0].tab);
    free(T[1].tab);

    return 0;
}
