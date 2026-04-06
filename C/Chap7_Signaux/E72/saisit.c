#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    int x;
    pid_t pid;

    printf("Entrer un entier : ");
    scanf("%d", &x);

    /* écrire dans fichier */
    FILE* f = fopen("/tmp/entier.txt", "w");

    if(f == NULL)
    {
        perror("Erreur fichier");
        return 1;
    }

    fprintf(f, "%d", x);
    fclose(f);

    printf("Entrer le PID du programme affiche : ");
    scanf("%d", &pid);

    /* envoyer signal */
    kill(pid, SIGUSR1);

    printf("Signal envoyé !\n");

    return 0;
}
