#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int  main(int argc, char*argv[])
{
	char commande[200];
	
	snprintf(commande, sizeof(commande),"cp -r * %s", argv[1]);
	system(commande);
	printf("execution du commande...");
	return  0;
}
