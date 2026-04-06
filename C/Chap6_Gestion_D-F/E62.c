#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define LIMITE 1048576  // 1 Mo

void parcourir(const char* chemin)
{
    DIR* dir = opendir(chemin);

    if(dir == NULL)
    {
        perror("Erreur ouverture dossier");
        return;
    }

    struct dirent* entry;

    while((entry = readdir(dir)) != NULL)
    {
        /* ignorer . et .. */
        if(strcmp(entry->d_name, ".") == 0 ||
           strcmp(entry->d_name, "..") == 0)
            continue;

        char path[512];
        snprintf(path, sizeof(path), "%s/%s", chemin, entry->d_name);

        struct stat st;

        if(stat(path, &st) == 0)
        {
            if(S_ISREG(st.st_mode)) // vérifier si c’est un fichier
            {
                if(st.st_size > LIMITE)
                {
                    printf("Fichier: %s | Taille: %ld | UID: %d\n",
                           path,
                           st.st_size,
                           st.st_uid);
                }
            }
        }
    }

    closedir(dir);
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Usage: %s <repertoire1> <repertoire2> ...\n", argv[0]);
        return 1;
    }

    for(int i = 1; i < argc; i++)
    {
        printf("\n--- Répertoire: %s ---\n", argv[i]);
        parcourir(argv[i]);
    }

    return 0;
}
