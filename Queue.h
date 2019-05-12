//
// Created by charl on 2019-05-12.
//

#ifndef HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_QUEUE_H
#define HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_QUEUE_H

#include "Elementary.h"

LinkQueue* createQueue();
void EnQueue(LinkQueue* queue, void* data);
void* DeQueue(LinkQueue* queue);
int isQueueEmpty(LinkQueue* queue);
void DestroyQueue(LinkQueue* queue);

#endif //HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_QUEUE_H
