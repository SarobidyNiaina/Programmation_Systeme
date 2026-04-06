#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main( ) 
{	
	char *fd_str = getenv("FD_TUBE");
	if ( fd_str == NULL )
	{
		printf("varable d'env non trouver..\n");
		return 1;
	}
	int fd = atoi(fd_str);
	char B[40];
	read(fd, B, sizeof(B));
	printf("Message reçu: %s\n", B);

    return 0;
}
