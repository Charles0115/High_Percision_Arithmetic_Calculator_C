//
// Created by charl on 2019-05-12.
//

#include "Queue.h"

LinkQueue* createQueue()
{
    LinkQueue* queue = (LinkQueue*) malloc (sizeof(LinkQueue));
    queue->front=NULL;
    queue->rear=NULL;
    queue->count = 0;
    return queue;
}

void EnQueue(LinkQueue* queue, void* data)
{
    ListNode* s = (ListNode*) malloc (sizeof(ListNode));
    s->data = data;
    s->next = NULL;

    if(isQueueEmpty(queue))
    {
        queue->front=s;
        queue->rear=s;
        queue->count = 1;
    }
    else
    {
        queue->rear->next = s;
        queue->rear = s;
        queue->count++;
    }
}

void* DeQueue(LinkQueue* queue)
{
    ListNode* p;
    p = queue->front;
    void* output = p->data;
    queue->front = p->next;
    queue->count--;
    if(queue->front == NULL)
        queue->rear = NULL;

    free(p);
    return output;
}

int isQueueEmpty(LinkQueue* queue)
{
    return ((queue->rear == NULL) && (queue->front == NULL));
}

void DestroyQueue(LinkQueue* queue)
{
    while(!isQueueEmpty(queue))
    {
        ListNode* p;
        p = queue->front;
        queue->front = p->next;
        if(queue->front == NULL)
            queue->rear = NULL;
        free(p);
        printf("yes\n");
    }

    free(queue);
}
