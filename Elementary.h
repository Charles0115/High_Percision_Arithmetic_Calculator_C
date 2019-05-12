//
// Created by charl on 2019-05-12.
//

#ifndef HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_ELEMENTARY_H
#define HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_ELEMENTARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode
{
    void* data;
    struct ListNode* next;
}ListNode;

typedef struct LinkStack
{
    ListNode* top;
    int count;
}LinkStack;

typedef struct LinkQueue
{
    ListNode* front;
    ListNode* rear;
    int count;
}LinkQueue;

#endif //HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_ELEMENTARY_H
