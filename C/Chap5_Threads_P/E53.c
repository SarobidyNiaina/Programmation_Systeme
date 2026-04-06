#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
	int Nb_el;
	int tab[5];
	int x;
}TypeTab;
void* afficher(void *arg)
{
	int t = *(int*)arg;
	printf("le check est %d \n", t);
	return NULL;
}
int main()
{
	TypeTab t1;
	t1.Nb_el = 5;
	int check;
	int tep = t1.Nb_el, x1;
	    pthread_t thread;
	//int tab[5];
	printf("entez le nombre x : ");
	scanf("%d", &x1);
	t1.x = x1;

	srand(time(NULL));
	for (int i = 0; i<5 ; i++ )
	{
		t1.tab[i] = rand() % 99;
	}
	//comparaison
	for (int i = 0; i<5 ; i++ )
        {
		printf("%d et %d \n", t1.tab[i], t1.x);
		getchar();
             if( t1.tab[i] == t1.x )
		{
			printf("trouver\n");
			check = 1;
			break;
		}
		else {check = 0;}	
        }


    pthread_create(&thread, NULL, afficher, &check);

    pthread_join(thread, NULL);

    return 0;
}
