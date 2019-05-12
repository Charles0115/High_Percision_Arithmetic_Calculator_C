//
// Created by charl on 2019-05-12.
//

#ifndef HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_STACK_QUEUE_H
#define HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_STACK_QUEUE_H

#include "Elementary.h"

LinkStack* createStack();
int isStackEmpty(LinkStack* stack);
void push(LinkStack* stack, void* data);
void* pop(LinkStack* stack);
void DestroyStack(LinkStack* stack);

#endif //HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_STACK_QUEUE_H
