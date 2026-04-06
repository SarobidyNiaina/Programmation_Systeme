#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int  main(int argc, char**argv)
{   
	int a, b;
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    printf("la somme est %d\n", a + b)
	return  0;
}
