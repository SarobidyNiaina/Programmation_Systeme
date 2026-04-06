#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int  main( )
{
	char n[100];
	printf("veuillez entrez le nom du ficiher: ");
	fgets(n, sizeof(n), stdin);
	n[strcspn(n,"\n")] = '\0';
	char *args[] = {"/usr/bin/emacs", n , NULL};
	execv("/usr/bin/emacs", args);

	printf("erreur lord de l'entrea d'emacs");

	return  0;
}
