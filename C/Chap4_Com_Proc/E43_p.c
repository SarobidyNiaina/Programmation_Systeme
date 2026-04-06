#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main() 
{
    int fd[2];
    pipe(fd);

    if (fork() == 0) 
    {
        // FILS

        char fd_str[10];
        sprintf(fd_str, "%d", fd[0]);

        char *args[] = {"./fils", fd_str, NULL};

        execv("./fils", args);
    }
    else 
    {
        // PÈRE

        close(fd[0]); // fermer lecture

        write(fd[1], "Bonjour depuis le père", strlen( "Bonjour depuis le père") + 1);
	wait(NULL);
        close(fd[1]);
    }

    return 0;
}
