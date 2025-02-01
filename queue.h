#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct process {
    int pid;
    int burst;
} QueueEntry;

typedef struct queuenode {
    QueueEntry entry;
    struct queuenode *next;
} QueueNode;

typedef struct queue {
    QueueNode *front;
    QueueNode *rear;
    int size;
} Queue;

void CreateQueue(Queue *pq);
int QueueFull(Queue *pq);
int Append(QueueEntry e, Queue *pq);
int QueueEmpty(Queue *pq);
void Serve(QueueEntry *pe, Queue *pq);
void QueueTop(QueueEntry *pe, Queue *pq);
int QueueSize(Queue *pq);
void ClearQueue(Queue *pq);
void TraverseQueue(Queue *pq, void (*pf)(QueueEntry));

#endif // QUEUE_H_INCLUDED