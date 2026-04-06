#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    pid_t pid = fork();

    if(pid < 0)
    {
        perror("Erreur fork");
        return 1;
    }

    if(pid == 0)
    {
        while(1)
        {
            printf("Fils : je travaille...\n");
            sleep(1);
        }
    }

    else
    {
        char c;

        while(1)
        {
            printf("\nMenu:\n");
            printf("s : stop fils\n");
            printf("r : reprendre fils\n");
            printf("q : quitter\n");
            printf("Choix : ");

            scanf(" %c", &c);

            if(c == 's')
            {
                kill(pid, SIGSTOP);
                printf("Fils suspendu\n");
            }
            else if(c == 'r')
            {
                kill(pid, SIGCONT);
                printf("Fils repris\n");
            }
            else if(c == 'q')
            {
                kill(pid, SIGKILL);
                printf("Fils tué\n");
                break;
            }
        }
    }

    return 0;
}
