#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main ()
{
	pid_t f;
	int check = -1;
	int fd[2], fd1[2];
	pipe(fd);
	pipe(fd1);
	char R[50], bufferW[50];
	f = fork();
	if( f == -1 )
	{	printf("erreur dans le fork..");}

	if (f == 0 )
	{
			close(fd[0]);
		close(fd1[1]);
			read(fd1[0], &check, sizeof(int));
		if( check == 1 )
		{ printf("mot trouver ....\n");}
		else if(check > -1){printf("non trouver..\n");}
		printf("entrez le mot a rechercher: ");
		fgets( R, sizeof(R), stdin );
		R[strcspn(R, "\n")] = '\0';
		write(fd[1], R, strlen(R) + 1);
	}
	else
	{
			close(fd[1]);
		read(fd[0], bufferW, sizeof(bufferW));
		printf(" je suis le nouveau /%s/\n", bufferW);
		FILE *fp;
		char mot[50];
		fp = fopen("text.txt", "r");
		if( fp == NULL )
		{
			printf(" erreur d'ouverture du fivchier !!");
			return 1;
		}
		while( fscanf(fp, "%s", mot) != EOF )
		{
			if( strcmp(mot, bufferW) == 0 )
			{
				printf("mot trouver \n");
				check = 1;
			}
		}
		close(fd1[0]);
		write(fd1[1], &check, sizeof(int));
		fclose(fp);
		wait(NULL);
	}
	return 0;
}
