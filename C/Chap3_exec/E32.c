#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s repertoire_destination\n", argv[0]);
        exit(1);
    }
    printf("Copie du repertoire courant vers %s...\n", argv[1]);
    execlp("cp", "cp", "-r", ".", argv[1], NULL);
    perror("Erreur exec");
    return 1;
}
