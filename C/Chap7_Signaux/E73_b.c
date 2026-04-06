#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler_fils(int sig)
{
    printf("Fils %d : je meurs...\n", getpid());
    exit(0);
}

void handler_pere(int sig)
{
    printf("Père : je suis terminé\n");
    exit(0);
}

int main()
{
    pid_t fils[5];

    signal(SIGTERM, handler_pere);

    for(int i = 0; i < 5; i++)
    {
        fils[i] = fork();

        if(fils[i] == 0)
        {
            signal(SIGTERM, handler_fils);

            while(1)
            {
                printf("Fils %d actif\n", getpid());
                sleep(2);
            }
        }
    }

    int choix, num;

    while(1)
    {
        printf("\n1: stop\n2: resume\n3: kill\nChoix: ");
        scanf("%d", &choix);

        printf("Numéro du fils (0-4): ");
        scanf("%d", &num);

        if(num < 0 || num >= 5)
            continue;

        if(choix == 1)
            kill(fils[num], SIGSTOP);

        else if(choix == 2)
            kill(fils[num], SIGCONT);

        else if(choix == 3)
            kill(fils[num], SIGTERM); // IMPORTANT
    }

    return 0;
}
