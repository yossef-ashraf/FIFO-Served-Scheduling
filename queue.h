#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct process
{
    int pid;
    int burst;
} QueueEntry;
typedef struct queuenode
{
    QueueEntry entry;
    struct queuenode *next;
} QueueNode;


typedef struct queue
{
    QueueNode *front;
    QueueNode *rear;
    int size;
} Queue;

void CreateQueue(Queue *);

int QueueFull(Queue *);

//Pre: The Queue is initialized and not full
int Append(QueueEntry, Queue *);
//Post: The element e has been stored at the top of the Queue; and e does not change

int QueueEmpty(Queue *);

//Pre: The Queue is initialized and not empty
void Serve(QueueEntry *,Queue *);
//Post: The last element entered is returned and pointer change

//Pre: The Queue is initialized and not empty
void QueueTop(QueueEntry *,Queue *);
//Post: The last element entered is returned without pointer change

//Pre: Queue is initialized.
int QueueSize(Queue *);
//Post: returns how many elements exist.

//Pre: Queue is initialized.
void ClearQueue(Queue *);
//Post: destroy all elements; Queue looks initialized.

//Pre: Queue is initialized and not empty
void traverseQueue(Queue *,void (*pf)(QueueEntry));
//Post: All elements entered is returned
#endif // QUEUE_H_INCLUDED
