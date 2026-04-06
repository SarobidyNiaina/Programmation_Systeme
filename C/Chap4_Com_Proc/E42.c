#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main ()
{
	pid_t f;
	int fd[2], fd1[2];
	pipe(fd);
	pipe(fd1);
	f = fork();
	if( f == -1 )
	{	printf("erreur dans le fork..");}

	if (f == 0 )
	{
		close(fd[0]);
		close(fd1[1]);
		int check;
		char R[50];
                printf("entrez le mot a rechercher: ");
                fgets( R, sizeof(R), stdin );
		   R[strcspn(R, "\n")] = '\0';
		 write(fd[1], R, strlen(R) + 1);


		read(fd1[0], &check, sizeof(int));
		if( check == 1 )
		{ printf("mot trouver ....\n");}
		else {printf("non trouver..\n");}
		        close(fd[1]);
		        close(fd1[0]);
	}
	else
	{
	//	dup2(fd[0], STDIN_FILENO);
	//	close(fd[1]);

	//	close(fd1[0]);

		close(fd[1]);     // pas utilisé en lecture
		close(fd1[0]);    // pas utilisé en lecture

		dup2(fd[0], STDIN_FILENO);    // lire depuis le fils
		dup2(fd1[1], STDOUT_FILENO);  // écrire vers le fils
		  char bufferW[50];

		fgets(bufferW, sizeof(bufferW), stdin);
		bufferW[strcspn(bufferW, "\n")] = '\0';

		//read(fd[0], bufferW, sizeof(bufferW));
		//printf(" je suis le nouveau /%s/\n", bufferW);
		FILE *fp;
		char mot[50];
		int check = 0;
		fp = fopen("text.txt", "r");
		if( fp == NULL )
		{
		//	printf(" erreur d'ouverture du fivchier !!");
			return 1;
		}
		while( fscanf(fp, "%s", mot) != EOF )
		{
			if( strcmp(mot, bufferW) == 0 )
			{
				check = 1;
				break;
			}
		}
	//	dup2(fd1[1], STDOUT_FILENO);
	//	close(fd1[1]);
		printf("%d\n", check);
		//write(fd1[1], &check, sizeof(int));
		fclose(fp);
		fflush(stdout);
		        close(fd[0]);
        close(fd1[1]);
		wait(NULL);
		}
	return 0;
}
