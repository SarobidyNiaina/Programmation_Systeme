#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main ()
{
	printf("creation de proccessus\n");
	pid_t F;
	F = fork();
	if( F == -1 )
	{
		printf("Erreur dans le fork..");
		exit(0);
	}
	if( F == 0 )
	{
		printf("je suis le fils.."); 
		exit(0);
	}
	else
	{
		printf("je suis le père..");
		exit(0);
	}
	return 0;
}
