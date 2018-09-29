#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>
char fname[] = "/tmp/fifo1";
void central(double ct)
{
    printf("Central proc: Waiting for all processes to start!\n");
    int fd[9];
    double child_temps[5],last_temps[5];
    for(int i=1;i<=4;i++)
    {
        fname[9] = '0'+i; 
        mkfifo(fname,S_IRUSR);
        fd[i] = open(fname,O_WRONLY);
    }
    for(int i=5;i<=8;i++)
    {
        fname[9] = '0'+i; 
        mkfifo(fname,S_IRUSR);
        fd[i] = open(fname,O_RDONLY);
    }
    printf("Central proc: Done!\n");
    while(1)
    {
        double sum = 0;
        for(int i=1;i<=4;i++)
        {
            last_temps[i] = child_temps[i];
            read(fd[i+4],&child_temps[i],8);
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
        if(prevcnt==4)
        {
            double send = -1;
            for(int i=1;i<=4;i++)
            {
                write(fd[i],&send,8);
            }
            break;
        }
        else
        {
            for(int i=1;i<=4;i++)
            {
                write(fd[i],&ct,8);
            }
        }
    }
    for(int i=1;i<=8;i++)
    {
        close(fd[i]);
    }
}
void child(int me, double temp)
{
    fname[9] = '0'+me;
    printf("Proc %d: Waiting for all processes to start!\n",me);
    mkfifo(fname,S_IRUSR);
    int fdin = open(fname,O_RDONLY);
    fname[9] = '0'+me+4;
    int fdout = open(fname,O_WRONLY);
    printf("Proc %d: Done!\n",me);
    while(1)
    {
        write(fdout,&temp,8);
        double ct;
        read(fdin,&ct,8);
        if(ct==-1) break;
        temp = (temp*3+2*ct)/5;
    }
    printf("Proc %d: Stabilized temperature=%.4lf\n",me,temp);
    close(fdin);
    close(fdout);
}
int main()
{
    printf("Enter central temp:");
    double ct,t[5];
    scanf("%lf",&ct);
    for(int i=1;i<=4;i++)
    {
        printf("Enter initial temp %d:",i);
        scanf("%lf",&t[i]);
    }
    //create 4 child and par for central
    for(int i=1;i<=4;i++)
    {
        if(!fork())
        {
            child(i,t[i]);
            return 0;
        }
    }
    central(ct);
    return 0;
}