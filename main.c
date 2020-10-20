/******************************************************************************

To compile: 
gcc main.c -o <output-name> -lpthread

To run:
./<output-file>

(in this case)
./Thread_Counter

*******************************************************************************/
#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 

int MAX = 10;
int count = 0;

sem_t sem; 

void *even(void *arg) {
    
    printf("This is even thread()\n");
    sem_wait(&sem);
    while(count < MAX) {
        sem_wait(&sem);

          if(count % 2 == 0)
              printf("%d ", count++);
              
        sem_post(&sem);
    }
    
    pthread_exit(0);
}

void *odd(void *arg) {
    
     printf("This is odd thread()\n");
     sem_post(&sem);
     while(count < MAX) {
        sem_wait(&sem);

         if(count % 2 == 1)
             printf("%d ", count++);
             
         sem_post(&sem);
     }

     pthread_exit(0);
}

int main() {
    
    pthread_t t1;
    pthread_t t2;
    
    sem_init(&sem, 0, 1); 
    pthread_create(&t2, 0, &odd, NULL);
    pthread_create(&t1, 0, &even, NULL);
    
    pthread_join(t1, 0);
    pthread_join(t2, 0);

    sem_destroy(&sem);

    return 0;
}