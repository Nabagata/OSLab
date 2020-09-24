#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
 
#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (ph_num+4)%N
#define RIGHT (ph_num+1)%N
 
sem_t mutex;
class monitor{
    public: 
    sem_t S[N];
    int state[N];

    void* philospher(void *num)
    {
        int i = *(int*)num;
        sleep(1);
        this->take_fork(i);
        sleep(0);
        this->put_fork(i);
    }
     
    void take_fork(int ph_num)
    {
        sem_wait(&mutex);
        this->state[ph_num] = HUNGRY;
        printf("P %d is Hungry\n",ph_num+1);
        this->test(ph_num);
        sem_post(&mutex);
        sem_wait(&this->S[ph_num]);
        sleep(1);
    }
     
    void test(int ph_num)
    {
        if (this->state[ph_num] == HUNGRY && this->state[LEFT] != EATING && this->state[RIGHT] != EATING)
        {
            this->state[ph_num] = EATING;
            sleep(2);
            printf("P %d takes Fork %d and %d\n",ph_num+1,LEFT+1,ph_num+1);
            printf("P %d is Eating\n",ph_num+1);
            sem_post(&this->S[ph_num]);
        }
    }
     
    void put_fork(int ph_num)
    {
        sem_wait(&mutex);
        this->state[ph_num] = THINKING;
        printf("P %d putting Fork %d and %d down\n",ph_num+1,LEFT+1,ph_num+1);
        printf("P %d is Thinking\n",ph_num+1);
        this->test(LEFT);
        this->test(RIGHT);
        sem_post(&mutex);
    }
};
monitor M;

void* init(void *num){
    M.philospher(num);
}
 
int phil_num[N]={0,1,2,3,4};
 
int main()
{
    int i;
    pthread_t thread_id[N];
    sem_init(&mutex,0,1);
    for(i=0;i<N;i++)
        sem_init(&M.S[i],0,0);
    for(i=0;i<N;i++)
    {
        pthread_create(&thread_id[i],NULL,init,(void*)&phil_num[i]);
        printf("P %d is Thinking\n",i+1);
    }
    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL);
}
