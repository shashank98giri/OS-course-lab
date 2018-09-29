#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#define abs(x) ((x<0)?-(x):(x))

typedef struct{
    double ct,temp[5];
    bool rw[5],rwct[5];
}data;
void Write(double *ele,bool *chk, bool matchwith, double *data)
{
    while((*chk)==matchwith);
    (*chk)=matchwith;
    *ele = *data;
}
void Read(double *ele,bool *chk, bool matchwith, double *data)
{
    while((*chk)==matchwith);
    (*chk)=matchwith;
    *data = *ele;
}
void Sync(data *info)
{
    int cnt = 0;
    while(cnt<4)
    {
        cnt = 4;
        for(int i=1;i<=4;i++)
            cnt -= info->rwct[i];
    }                
}
void central(int shmid, double ct)
{
    chkerror();
    data *info = (data*)shmat(shmid,NULL,SHM_RND);
    chkerror();
    double child_temps[5],last_temps[5];
    while(1)
    {
        double sum = 0;
        for(int i=1;i<=4;i++)
        {
            last_temps[i] = child_temps[i];
            Read(&(info->temp[i]),&(info->rw[i]),0,&(child_temps[i]));
            sum += child_temps[i];
            printf("Proc %d reported temperature=%.4lf\n",i,child_temps[i]);
        }
        ct = (2*ct+sum)/6;
        printf("New central temp=%.4lf\n",ct);
        int prevcnt = 0;
        for(int i=1;i<=4;i++)
        {
            if(abs(child_temps[i]-last_temps[i])==0) prevcnt++;
        }
        Sync(info);
        if(prevcnt==4)
        {
            double send = -1;
            for(int i=1;i<=4;i++)
            {
                Write(&(info->ct),&(info->rwct[i]),1,&send);
            }
            break;
        }
        else
        {
            for(int i=1;i<=4;i++)
            {
                Write(&(info->ct),&(info->rwct[i]),1,&ct);
            }
        }
    }
    shmdt(info);
}
void child(int shmid,int me, double temp)
{
    data *info = (data*)shmat(shmid,NULL,SHM_RND);
    chkerror();
    bool rw = 1;
    while(1)
    {
        Write(&(info->temp[me]),&(info->rw[me]),1,&temp);
        double ct;
        Read(&(info->ct),&(info->rwct[me]),0,&ct);
        if(ct==-1) break;
        temp = (temp*3+2*ct)/5;
    }
    printf("Proc %d: Stabilized temperature=%.4lf\n",me,temp);
    shmdt(info);
}
int main()
{
    int shmid = shmget(IPC_PRIVATE,sizeof(data),0777|IPC_CREAT);
    printf("Enter central temp:");
    double ct,t[5];
    scanf("%lf",&ct);
    for(int i=1;i<=4;i++)
    {
        printf("Enter initial temp %d:",i);
        scanf("%lf",&t[i]);
    }
    
    for(int i=1;i<=4;i++)
    {
        if(!fork())
        {
            child(shmid,i,t[i]);
            return 0;
        }
    }
    central(shmid,ct);
    return 0;
}