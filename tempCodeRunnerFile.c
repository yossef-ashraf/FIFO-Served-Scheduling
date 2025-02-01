#include <stdio.h>
#include <stdlib.h>
// #include "queue.h"
#include "queue.c"

int isValid(char *);
void setNumProcess(int *);
void setProcessDetail(int ,Queue *);
void displayProcessDetail(int ,float *,Queue *,int *,int *);
void displayAvg(float ,int );
void displayGantChart(int ,int *,int *);

int main()
{
    int np;
    float sum=0;
    Queue q;
    CreateQueue(&q);

    setNumProcess(&np);
    setProcessDetail(np,&q);

    int wt[np];
    int pid[np];
    displayProcessDetail(np,&sum,&q,&wt,&pid);
    displayAvg(sum,np);
    displayGantChart(np,&wt,&pid);

    return 0;
}
int isValid(char *cptr)
{
    while (*cptr != '\0')
    {
        if (isdigit(*cptr) == 0)
            return 0;
        cptr++;
    }
    return 1;
};
void setNumProcess(int *np)
{
    char nps[10];
    printf("Enter Number of Processes:");
    scanf("%s",&nps);
    if (!isValid(&nps))
    {
        printf("Please enter number of process in correct positive format\n");
        setNumProcess(np);
    }
    else
    {
        *np =atoi(nps);
    }
};
void setProcessDetail(int np,Queue *prq)
{
    QueueEntry p;
    char pids[10],burts[10];
    printf("PID     Burst\n");
    int i =0;
    while(i < np)
    {
        scanf("%s %s",pids,burts);
        if (isValid(&pids) && isValid(&burts))
        {
            p.pid=atoi(pids);
            p.burst=atoi(burts);
            if(!QueueFull(prq))
                if(!Append(p,prq))
                    printf("can not Append PID/n");
            i++;
        }
        else
        {
            printf("Please enter pid and burst in valid positive integer format \n");
        }
    }
};
void displayProcessDetail(int np,float *sum,Queue *prq,int *wt,int *pid)
{
    QueueEntry p;
    printf("---------------\n");
    printf("PID\t | WT     \n");
    printf("---------------\n");
    int i = 0;
    wt[0]=0;
    while(!QueueEmpty(prq))
    {
        Serve(&p,prq);
        printf("%d\t | %d\n",p.pid,wt[i]);
        *sum+=wt[i];
        pid[i]=p.pid;
        i++;
        wt[i]=p.burst+wt[i-1];
    }
    printf("---------------\n");
};
void displayAvg(float sum,int np)
{
    printf("\nAverage Waiting Time=%f\n",sum/np);
};
void displayGantChart(int np,int *wt,int *pid)
{
    int j=0;
    int k=0;
    printf("\n");

    for(k=0; k<np*8; k++) printf("-");
    printf("\n");
    j=0;
    while(j<np)
    {
        printf("P%d\t",pid[j++]);
    }
    printf("\n");
    for(k=0; k<np*8; k++) printf("-");

    j=0;
    printf("\n");
    while(j<np+1)
    {
        printf("%d\t",wt[j++]);
    }

};
