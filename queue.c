#include <stdlib.h>
#include "queue.h"

void CreateQueue(Queue *pq) {
    pq->front = NULL;
    pq->rear = NULL;
    pq->size = 0;
}

int QueueFull(Queue *pq) {
    return 0;  // Linked implementation is never full if memory is available
}

int Append(QueueEntry e, Queue *pq) {
    QueueNode *pn = (QueueNode *)malloc(sizeof(QueueNode));
    if (!pn)
        return 0;
    
    pn->entry = e;
    pn->next = NULL;
    
    if (!pq->rear)
        pq->front = pn;
    else
        pq->rear->next = pn;
    
    pq->rear = pn;
    pq->size++;
    return 1;
}

int QueueEmpty(Queue *pq) {
    return !pq->size;
}

void Serve(QueueEntry *pe, Queue *pq) {
    if (QueueEmpty(pq))
        return;
        
    QueueNode *pn = pq->front;
    *pe = pn->entry;
    pq->front = pn->next;
    free(pn);
    
    if (!pq->front)
        pq->rear = NULL;
    pq->size--;
}

void QueueTop(QueueEntry *pe, Queue *pq) {
    if (!QueueEmpty(pq))
        *pe = pq->front->entry;
}

int QueueSize(Queue *pq) {
    return pq->size;
}

void ClearQueue(Queue *pq) {
    while (pq->front) {
        pq->rear = pq->front->next;
        free(pq->front);
        pq->front = pq->rear;
    }
    pq->size = 0;
}

void TraverseQueue(Queue *pq, void (*pf)(QueueEntry)) {
    for (QueueNode *pn = pq->front; pn; pn = pn->next) {
        (*pf)(pn->entry);
    }
}