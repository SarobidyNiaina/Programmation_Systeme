#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* handler du signal */
void handler(int sig)
{
    FILE* f = fopen("/tmp/entier.txt", "r");

    if(f == NULL)
    {
        perror("Erreur ouverture fichier");
        return;
    }

    int x;
    fscanf(f, "%d", &x);
    fclose(f);

    printf("Valeur reçue : %d\n", x);
}

int main()
{
    printf("PID de affiche : %d\n", getpid());

    signal(SIGUSR1, handler);

    /* attente infinie */
    while(1)
    {
        sleep(1);
    }

    return 0;
}
