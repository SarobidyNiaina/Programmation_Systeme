#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int  main(   )
{
	char commande[200], c[300];;
	while ( 1 )
	{
		printf("veuillez entrez le repertoir destinataire(ou 1 pour quitter): ");
		 fgets(commande, sizeof(commande), stdin );
		commande[strcspn(commande,"\n")] = '\0';
		if( strcmp(commande, "exit" ) == 0 )
                { 
                       break;
                }
		  snprintf(c, sizeof(c), "cp -r ./* \"%s\"", commande);

//		snprintf(c, sizeof(c),"cp -r ./* \"%s\"", commande);
		system(c);
		printf("execution du commande...");
	}
	return  0;
}

