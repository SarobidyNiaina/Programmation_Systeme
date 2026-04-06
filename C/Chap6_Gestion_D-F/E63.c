#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main()
{
    int n;

    printf("Donner la taille du tableau : ");
    scanf("%d", &n);

    int* tab = malloc(n * sizeof(int));

    if(tab == NULL)
    {
        printf("Erreur allocation\n");
        return 1;
    }

    /* saisie */
    for(int i = 0; i < n; i++)
    {
        printf("tab[%d] = ", i);
        scanf("%d", &tab[i]);
    }

    /* ouverture fichier binaire */
    FILE* f = fopen("tableau.bin", "wb");

    if(f == NULL)
    {
        printf("Erreur ouverture fichier\n");
        return 1;
    }

    /* écrire le tableau */
    fwrite(&n, sizeof(int), 1, f);        // taille
    fwrite(tab, sizeof(int), n, f);       // données

    fclose(f);

    /* changer les permissions : 644 */
    chmod("tableau.bin", 0644);

    printf("Tableau sauvegardé avec succès.\n");

    free(tab);

    return 0;
}
