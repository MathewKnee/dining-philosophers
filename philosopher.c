#include <sys/stat.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#define SEM_KEY 1221


static struct sembuf buf;

void v(int semid, int semnum)
{
   buf.sem_num = semnum;
   buf.sem_op = 1;
   buf.sem_flg = 0;
   if (semop(semid, &buf, 1) == -1)
   {
       perror("V operation");
       exit(1);
   }
}

void p(int semid, int semnum)
{
   buf.sem_num = semnum;
   buf.sem_op = -1;
   buf.sem_flg = 0;
   if (semop(semid, &buf, 1) == -1)
   {
       perror("P operation");
       exit(1);
   }
}

int main(int argc, char const *argv[])
{   
    srand(time(NULL)+getpid());
    int semID = semget(SEM_KEY, 5, S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL);
    short vals[5] = {1,1,1,1,1};
    if(semID > 0){
        semctl(semID,0,SETALL,vals);
    }else{
        semID = semget(SEM_KEY, 5, S_IRUSR | S_IWUSR); 
    }
    int philosopher_num = atoi(argv[1]);
    while(1){
        
        printf("Philosopher %d is waiting to eat...\n",philosopher_num);
        if(philosopher_num%2 ==0){
            p(semID,philosopher_num);
        }else{
            p(semID,philosopher_num-1);
        }
        if(philosopher_num%2 ==0){
            p(semID,philosopher_num-1);
        }else{
            p(semID,philosopher_num%5);
        }
        int eating_time = rand()%10 +1;
        printf("Philosopher %d is going to eat for %d seconds...\n",philosopher_num,eating_time);
        sleep(eating_time);
        if(philosopher_num%2 ==0){
            v(semID,philosopher_num);
        }else{
            v(semID,philosopher_num-1);
        }
        if(philosopher_num%2 ==0){
            v(semID,philosopher_num-1);
        }else{
            v(semID,philosopher_num%5);
        }
        printf("Philosopher %d finished eating.\n",philosopher_num);
        int contemplating_time = rand()%10 +1;
        printf("Philosopher %d is going to contemplate for %d seconds...\n",philosopher_num,contemplating_time);
        sleep(contemplating_time);
        printf("Philosopher %d finished contemplating.\n",philosopher_num);
    }
    return 0;
}
