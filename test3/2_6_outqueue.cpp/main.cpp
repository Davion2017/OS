#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NULL 0
typedef struct processpcb
{
    int id; /* 进程控制块编号*/
    struct processpcb *next;
} node;
int n;
node *creat(void) /* 建立进程控制块队列表*/
{
    //填补程序
    node *head, *p1, *p2;
    head = p1 = (node*)malloc(sizeof(node));
    p1->next = NULL;
    p2 = (node*)malloc(sizeof(node));
    scanf("%d", &p2->id);
    while(p2->id > 0)
    {
        if(head->next == NULL)
        {
            head->id = p2->id;
            head->next = p1;
        }
        else
        {
            p1->next = p2;
            p2->next = NULL;
            p1 = p2;
        }
        p2 = (node*)malloc(sizeof(node));
        scanf("%d", &p2->id);
    }
    return head;
}
node *del(node *head,int pcb) /* 根据进程 PCB  的 id  找到需要出列的进程*/
{
    //填补程序
    node *p = head, *pre = NULL;
    if(head->id == pcb)
    {
        head = head->next;
        free(p);
        return head;
    }
    while(p)
    {
        if(p->id == pcb)
        {
            pre->next = p->next;
            free(p);
            return head;
        }
        pre = p;
        p = p->next;
    }
    printf("进程不存在！\n");
    return head;
}
void print (node *head) /* 输出链表*/
{
    //填补程序
    node *p = head;
    while(p)
    {
        printf("%d\t", p->id);
        p = p->next;
    }
    printf("\n");
}
int main()
{
    //填补程序：模拟建立进程控制块队列和出队过程
    int x;
    node *head;
    printf("创建进程队列：");
    head = creat();
    print(head);
    while(head)
    {
        printf("输入要出列的进程：");
        scanf("%d", &x);
        head = del(head, x);
        print(head);
    }
    return 0;
}
