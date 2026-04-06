#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int  main(   )
{
	char commande[200], c[300];
	while ( 1 )
	{
		printf("veuillez entrez le nom du fichier : ");
		 fgets(commande, sizeof(commande), stdin );
		commande[strcspn(commande,"\n")] = '\0';
		if( strcmp(commande, "exit" ) == 0 )
                { 
                       break;
                }
		pid_t f = fork();
		if( f == 0 )
		{
			char *args[] = {"/usr/bin/emacs", commande, NULL};
			execv("/usr/bin/emacs", args);
			printf("Erreur d'execution...");
		}
		else if ( f>0 )
		{
			wait(NULL);
		}
		else 
		{
				printf(" erreur du fork");
		}
	}
	return  0;
}

