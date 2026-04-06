#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    pid_t fils[5];

    /* création des 5 fils */
    for(int i = 0; i < 5; i++)
    {
        fils[i] = fork();

        if(fils[i] == 0)
        {
            while(1)
            {
                printf("Fils %d actif\n", i);
                sleep(2);
            }
        }
    }

    /* PERE */
    int choix, num;

    while(1)
    {
        printf("\n1: stop\n2: resume\n3: kill\nChoix: ");
        scanf("%d", &choix);

        printf("Numéro du fils (0-4): ");
        scanf("%d", &num);

        if(num < 0 || num >= 5)
        {
            printf("Num invalide\n");
            continue;
        }

        if(choix == 1)
        {
            kill(fils[num], SIGSTOP);
        }
        else if(choix == 2)
        {
            kill(fils[num], SIGCONT);
        }
        else if(choix == 3)
        {
            kill(fils[num], SIGKILL);
        }
    }

    return 0;
}
