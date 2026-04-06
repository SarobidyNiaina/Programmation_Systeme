#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    pid_t f;
    int fd[2], fd1[2];

    pipe(fd);
    pipe(fd1);

    f = fork();

    if (f == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // ===================== FILS =====================
    if (f == 0) {
        close(fd[0]);
        close(fd1[1]);

        char R[50];
        int check;

        printf("Entrez le mot à rechercher: ");
        fflush(stdout);

        fgets(R, sizeof(R), stdin);
        R[strcspn(R, "\n")] = '\0';

        write(fd[1], R, strlen(R) + 1);

        read(fd1[0], &check, sizeof(int));

        if (check == 1)
            printf("Mot trouvé\n");
        else
            printf("Non trouvé\n");

        close(fd[1]);
        close(fd1[0]);
    }

    // ===================== PÈRE =====================
    else {
        close(fd[1]);
        close(fd1[0]);

        dup2(fd[0], STDIN_FILENO);
        dup2(fd1[1], STDOUT_FILENO);

        char bufferW[50];
        int check = 0;

        scanf("%49s", bufferW);

        FILE *fp = fopen("text.txt", "r");
        if (!fp) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        char mot[50];

        while (fscanf(fp, "%49s", mot) == 1) {
            if (strcmp(mot, bufferW) == 0) {
                check = 1;
                break;
            }
        }

        fclose(fp);

        printf("%d\n", check);
        fflush(stdout);

        close(fd[0]);
        close(fd1[1]);

        wait(NULL);
    }

    return 0;
}
