#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main ()
{
	printf("creation de proccessus\n");
	pid_t F1;
	for (int i=0 ; i<5 ; i++ )
	{
		F1 = fork();
		if( F1 == 0 )
		{
			printf("%d :je suis le fils.pid=%d / %d\n", i+1,getpid(), getppid());
			return 0;;
		}
		//break;
	}
	for (int i=0 ; i<5 ; i++ )
	{
		wait(NULL);
	}
	printf("je suis le père..pid=%d", getpid());
	return 0;
}
