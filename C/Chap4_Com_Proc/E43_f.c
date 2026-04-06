#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main( int argc, char**argv) 
{	
	int fd = atoi(argv[1]);
	char B[40];
	read(fd, B, sizeof(B));
	printf("Message reçu: %s\n", B);

    return 0;
}
