#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main()
{
    int n;

    printf("Donner la taille : ");
    scanf("%d", &n);

    int* tab = malloc(n * sizeof(int));

    for(int i = 0; i < n; i++)
    {
        printf("tab[%d] = ", i);
        scanf("%d", &tab[i]);
    }

    FILE* f = fopen("data.bin", "wb");

    if(f == NULL)
    {
        perror("Erreur fichier");
        return 1;
    }

    fwrite(tab, sizeof(int), n, f);

    fclose(f);

    chmod("data.bin", 0644);

    free(tab);

    return 0;
}
