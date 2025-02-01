#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue.h"
#include "queue.c"

int isValid(const char *cptr) {
    if (!cptr || *cptr == '\0')
        return 0;
        
    while (*cptr != '\0') {
        if (!isdigit(*cptr))
            return 0;
        cptr++;
    }
    return 1;
}

void setNumProcess(int *np) {
    char nps[10];
    printf("Enter Number of Processes: ");
    scanf("%s", nps);
    
    if (!isValid(nps)) {
        printf("Please enter number of process in correct positive format\n");
        setNumProcess(np);
    } else {
        *np = atoi(nps);
        if (*np <= 0) {
            printf("Number of processes must be positive\n");
            setNumProcess(np);
        }
    }
}

void setProcessDetail(int np, Queue *prq) {
    QueueEntry p;
    char pids[10], burts[10];
    printf("PID     Burst\n");
    
    for (int i = 0; i < np; i++) {
        scanf("%s %s", pids, burts);
        if (isValid(pids) && isValid(burts)) {
            p.pid = atoi(pids);
            p.burst = atoi(burts);
            
            if (p.burst <= 0) {
                printf("Burst time must be positive\n");
                i--;
                continue;
            }
            
            if (!Append(p, prq)) {
                printf("Failed to add process. Memory allocation error.\n");
                exit(1);
            }
        } else {
            printf("Please enter PID and burst in valid positive integer format\n");
            i--;
        }
    }
}

void displayProcessDetail(int np, float *sum, Queue *prq, int *wt, int *pid) {
    QueueEntry p;
    printf("\n------------------\n");
    printf("PID\t | Waiting Time\n");
    printf("------------------\n");
    
    wt[0] = 0;
    int i = 0;
    
    while (!QueueEmpty(prq)) {
        Serve(&p, prq);
        printf("%d\t | %d\n", p.pid, wt[i]);
        *sum += wt[i];
        pid[i] = p.pid;
        i++;
        if (i < np) {
            wt[i] = p.burst + wt[i-1];
        }
    }
    printf("------------------\n");
}

void displayAvg(float sum, int np) {
    printf("\nAverage Waiting Time = %.2f\n", sum/np);
}

void displayGantChart(int np, int *wt, int *pid) {
    printf("\nGantt Chart:\n");
    
    // Top border
    for (int k = 0; k < np*8; k++) 
        printf("-");
    printf("\n");
    
    // Process IDs
    for (int j = 0; j < np; j++)
        printf("P%d\t", pid[j]);
    printf("\n");
    
    // Bottom border
    for (int k = 0; k < np*8; k++) 
        printf("-");
    printf("\n");
    
    // Timeline
    for (int j = 0; j <= np; j++)
        printf("%d\t", wt[j]);
    printf("\n");
}

int main() {
    int np;
    float sum = 0;
    Queue q;
    CreateQueue(&q);

    setNumProcess(&np);
    
    int *wt = (int *)malloc((np + 1) * sizeof(int));
    int *pid = (int *)malloc(np * sizeof(int));
    
    if (!wt || !pid) {
        printf("Memory allocation failed\n");
        return 1;
    }

    setProcessDetail(np, &q);
    displayProcessDetail(np, &sum, &q, wt, pid);
    displayAvg(sum, np);
    displayGantChart(np, wt, pid);

    free(wt);
    free(pid);
    ClearQueue(&q);
    
    return 0;
}