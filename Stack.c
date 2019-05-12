//
// Created by charl on 2019-05-12.
//

#include "Stack.h"

LinkStack* createStack()
{
    LinkStack* stack = (LinkStack*) malloc (sizeof(LinkStack));
    stack->count=0;
    return stack;
}

int isStackEmpty(LinkStack* stack)
{
    return (stack->count==0);
}

void push(LinkStack* stack, void* data)
{
    ListNode* s = (ListNode*) malloc (sizeof(ListNode));
    s->data = data;
    s->next=stack->top;
    stack->top=s;
    stack->count++;
}

void* pop(LinkStack* stack)
{
    ListNode* p;
    void* output = stack->top->data;
    p=stack->top;
    stack->top=stack->top->next;
    free(p);
    stack->count--;
    return output;
}

void DestroyStack(LinkStack* stack)
{
    while(!isStackEmpty(stack))
    {
        ListNode* p;
        p=stack->top;
        stack->top=stack->top->next;
        free(p);
        stack->count--;
        printf("yes\n");
    }

    free(stack);
}