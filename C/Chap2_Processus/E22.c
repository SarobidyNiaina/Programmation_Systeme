#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main ()
{
	printf("creation de proccessus\n");
	pid_t F1,F2;
		F1 = fork();
		if( F1 == 0 )
		{
			printf("je suis le fils 1 mon pid=%d / %d..\n", getpid(), getppid());
			return 0;
		}
                F2 = fork();
                if( F2 == 0 )
                {
                        printf("je suis le fils 2 mon pid=%d / %d..\n", getpid(), getppid());
                        return 0;
                }
	wait(NULL);
	wait(NULL);
	printf("je suis le père..pid=%d\n", getpid());
	return 0;
}
