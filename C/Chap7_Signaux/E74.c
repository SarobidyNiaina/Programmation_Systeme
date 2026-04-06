#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

int *tab;
int n;

jmp_buf env;

void handler(int sig)
{
    printf("Indice invalide ! Réessayez...\n");
    longjmp(env, 1);  // revenir au point sûr
}

int main()
{
    signal(SIGSEGV, handler);

    printf("Donner n : ");
    scanf("%d", &n);

    tab = malloc(n * sizeof(int));

     for(int i = 0; i < n; i++)
    {
        printf("tab[%d] = ", i);
        scanf("%d", &tab[i]);
    }

    int i;

    while(1)
    {
        if(setjmp(env) == 0)
        {
            printf("Donner indice i : ");
            scanf("%d", &i);

            printf("Valeur = %d\n", tab[i]);
            break;
        }
    }

    free(tab);
    return 0;
}
