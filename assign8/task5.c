#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define BUFFER_SIZE 10
typedef int bool;
sem_t *full,*empty,*mutex;
typedef struct{
    int q[BUFFER_SIZE];
    int st,en;
} data;
typedef struct{
    data *info;
    int val;
} push_pack;
void person_coming(push_pack *p)
{
    sleep(200);
    bool flag = 0;
    if(sem_trywait(empty) == -1){
        flag = 1;
    }
    sem_wait(mutex);
    if(flag){
        printf("Person %d is leaving. NO seat remaining\n",p->val);
        sem_post(mutex);
        int ex = 0;
        pthread_exit(&ex);
    }
    else
        printf("Customer %d seated on seat %d\n",p->val,p->info->en);    
    p->info->q[p->info->en] = p->val;
    p->info->en = (p->info->en+1)%BUFFER_SIZE;
    sem_post(mutex);
    sem_post(full);
    int ex = 0;
    pthread_exit(&ex);
}
void haircut(data *info)
{
    sleep(1);
    if(sem_trywait(full) == -1)
    {
        printf("Barber is sleeping!\n");
        return;
    }
    sem_wait(mutex);
    char ans = info->q[info->st];
    info->st = (info->st+1)%BUFFER_SIZE;
    printf("Customer %d had his haircut!\n",ans);    
    sem_post(mutex);
    sem_post(empty);
    
}
int main()
{
    sem_init(mutex,0,1);    
    sem_init(empty,0, BUFFER_SIZE);    
    sem_init(full,0,0);    
    data *info = (data*) malloc(sizeof(data));
    info->st = 0, info->en = 0;
    pthread_t a;
    push_pack p[100];
    for(int i=0;i<100;i++)
    {
        p[i].info = info;
        p[i].val = i+1;
        pthread_create(&a,NULL,person_coming,(void*)(p+i));
    }
    int cnt = 2000;
    while(cnt--)
    {
        haircut(info);
    }
    return 0;
}