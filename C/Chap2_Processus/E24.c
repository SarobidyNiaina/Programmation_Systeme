#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
int main ()
{
	time_t  start_time , end_time;
	srand(time(NULL));
	printf("creation de proccessus\n");
	pid_t F1,F2;
	 start_time = time(NULL);
		F1 = fork();
		if( F1 == 0 )
		{
			int seconde = rand() % 10 + 1;
			printf("je suis le fils 1 mon pid=%d / %d..\n", getpid(), getppid());
			sleep(seconde);
			return 0;
		}
                F2 = fork();
                if( F2 == 0 )
                {
			int seconde = rand() % 10 +1;
                        printf("je suis le fils 2 mon pid=%d / %d..\n", getpid(), getppid());
                        sleep(seconde);
			return 0;
                }
	waitpid(F1, NULL, 0);
	waitpid(F2, NULL, 0);
	end_time = time(NULL);
	double duree = difftime(end_time,start_time);
	printf("le programme a durree :%.0fseconde\n", duree);
	return 0;
}
