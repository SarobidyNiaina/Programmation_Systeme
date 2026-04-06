#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* f = fopen("data.bin", "rb");

    if(f == NULL)
    {
        perror("Erreur ouverture");
        return 1;
    }

    int* tab = NULL;
    int val;
    int n = 0;

    while(fread(&val, sizeof(int), 1, f) == 1)
    {
        tab = realloc(tab, (n + 1) * sizeof(int));

        if(tab == NULL)
        {
            printf("Erreur allocation\n");
            return 1;
        }

        tab[n] = val;
        n++;
    }

    fclose(f);

    /* affichage */
    printf("Tableau lu (%d éléments) :\n", n);

    for(int i = 0; i < n; i++)
    {
        printf("%d ", tab[i]);
    }

    printf("\n");

    free(tab);

    return 0;
}
