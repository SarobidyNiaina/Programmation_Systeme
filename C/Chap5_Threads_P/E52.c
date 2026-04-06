#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
void* afficher(void*arg)
{
	int *t = (int*) arg;
	for ( int i = 0 ; i<5 ; i++ )
	{
		printf("%d : %d \n", i, t[i]);
	}
	return NULL;
}
int main()
{
    pthread_t thread;
	int tab[5];
	srand(time(NULL));
	for (int i = 0; i<5 ; i++ )
	{
		tab[i] = rand() % 100;
	}
    pthread_create(&thread, NULL, afficher, tab);

    pthread_join(thread, NULL);

    return 0;
}
