#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "../include/dining_sem.h"

sem_t *forks;

int main(int argc, char *argv[])
{
	

	if (argc < 2) 
	{
	   fprintf (stderr, "call -number_of_philosophers\n");
	}
	
	int numberPhilosophers = atoi(strtok(argv[1],"-")); //Removes the "-" character included in the call command
	printf ("n=%d\n",numberPhilosophers);

        //There are N forks for N philosophers -> allocate the forks' semaphore
        forks = malloc (sizeof(sem_t) * numberPhilosophers);
	
}

void initializeSemaphores(sem_t *forks, int numberForks)
{
	int k; 
	for (k = 0; k < numberForks; k++)
		sem_init (&forks[k], 0, 1); //0 means the semaphore shared between threads. 1 because it is a binary semaphore
}
