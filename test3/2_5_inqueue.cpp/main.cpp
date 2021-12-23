#include <malloc.h>
#include <stdio.h>
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
node *append(node *head,node *q) /* 增加一个进程进入队列*/
{
    //填补程序
    node *p = head, *pre = NULL;
    while(p)
    {
        if(p->id == q->id)
        {
            printf("进程已存在！\n");
            return head;
        }
        pre = p;
        p = p->next;
    }
    pre->next = q;
    q->next = NULL;
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
    //填补程序：模拟建立进程控制块队列和入队过程
    node *head, *p;
    printf("创建进程队列：");
    head = creat();
    print(head);
    printf("请输入一个进程队列：");
    p = (node*)malloc(sizeof(node));
    scanf("%d",&p->id);
    while(p->id > 0)
    {
        append(head, p);
        print(head);
        p = (node*)malloc(sizeof(node));
        printf("请输入一个进程队列：");
        scanf("%d",&p->id);
    }
    return 0;
}
