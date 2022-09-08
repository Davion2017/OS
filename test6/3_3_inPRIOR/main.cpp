#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define NULL 0
typedef struct table
{
    int key; /* 进程 ID  号*/
    int priority; /* 优先数值*/
    char message[10]; /* 进程说明信息*/
    struct table *next;
} node;
node *insert(node *head,node *news)
{
    //填补程序
    int flag = 1;
    node *p = head, *pre = NULL;
    if(head == NULL)
    {
        news->next = NULL;
        head = news;
    }
    else if(news->priority > head->priority)
    {
        news->next = head;
        head = news;
    }
    else
    {
        while(p && flag)
        {
            if(p->priority < news->priority)
            {
                news->next = p;
                pre->next = news;
                flag = 0;
            }
            pre = p;
            p = p->next;
        }
        if(flag)
        {
            pre->next = news;
            news->next = NULL;
        }
    }
    return head;
} /* 将新进程插入到已经排序的队列中，对进程表按优先数从大到小排序*/
node *creat(void) /* 定义函数，调用 insert  函数建立排好序的进程链表*/
{
    //填补程序
    node *head, *p;
    head = (node*)malloc(sizeof(node));
    p = (node*)malloc(sizeof(node));
    head = NULL;
    printf("新建的进程控制表为：\nkey priority message\n");
    scanf("%d", &p->key);
    while(p->key > 0)
    {
        scanf("%d%s", &p->priority, &p->message);
        head = insert(head, p);
        p = (node*)malloc(sizeof(node));
        scanf("%d", &p->key);
    }
    return head;
}
void print (node *head) /* 输出链表*/
{
    //填补程序
    printf("The table is:\n");
    node *p = head;
    while(p)
    {
        printf("%d, %d, %s\n", p->key, p->priority, p->message);
        p = p->next;
    }
    printf("\n");
}
void rank_out(node *head) /* 模拟按优先数大小进程分级出队的过程*/
{
    //填补程序
    node *p;
    printf("key=%d, priority=%d, message=%s\n\n", head->key, head->priority, head->message);
    *p = *head;
    if(head->next == NULL)
        head = NULL;
    else
        *head = *head->next;
}
int main()
{
    //填补程序：模拟进程控制块队列按照优先级逐个出队过程
    node *head;
    int count = 0;
    head = creat();
    print(head);
    while(head)
    {
        count++;
        printf("第%d个出队进程为：\n", count);
        rank_out(head);
    }
    return 0;
}
