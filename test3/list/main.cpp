#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NULL 0
typedef struct processpcb
{
    int id; /* 进程控制块编号*/
    struct processpcb *next;
} node;
int n;
node *append(node *head,node *q) /* 增加一个进程进入队列*/
{
    node * p = head;
    while(p)
        p = p->next;
    p->next = q;
    return head;
}
node *creat(void) /* 建立进程控制块队列表*/
{
    node * head = (node*)malloc(sizeof(node));
    node * p;
    int x;
    scanf("%d", &x);
    while(x != 0)
    {
        p = (node*)malloc(sizeof(node));
        p->id = x;
        p->next = NULL;
        append(head, p);
        scanf("%d", &x);
    }
    return head;
}

void print (node *head) /* 输出链表*/
{
    node * p;
    while(p)
    {
        printf("%d ", p->id);
        p = p->next;
    }
}
int main()
{
    node * head;
    head  = creat();
    print(head);
    return 0;
}
