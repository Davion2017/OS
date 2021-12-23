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
node *creat(void) /* 定义函数，输入 ID  号和优先级，按照输入次序建立进程链表*/
{
    //填补程序
    int n = 0;
    node *head, *p1, *p2;
    printf("新建的进程控制表为：\nkey priority message\n");
    p1 = p2 = (node*)malloc(sizeof(node));
    scanf("%d", &p1->key);
    head = NULL;
    while(p1->key > 0)
    {
        scanf("%d%s", &p1->priority, &p1->message);
        n++;
        if(n == 1)
            head = p1;
        else
            p2->next = p1;
        p2 = p1;
        p1 = (node*)malloc(sizeof(node));
        scanf("%d", &p1->key);
    }
    p2->next = NULL;
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
node *processdo(node *head) /* 模拟当前最大优先数进程出队的过程*/
{
    //填补程序
    node *p, *p_max, *pre, *pp_max;
    pre = pp_max = NULL;
    p = p_max = head;
    while(p)
    {
        if(p->priority > p_max->priority)
        {
            pp_max = pre;
            p_max = p;
        }
        pre = p;
        p = p->next;
    }
    printf("key=%d,priority=%d,message=%s\n", p_max->key, p_max->priority, p_max->message);
    if(p_max == head)
    {
        head = head->next;
        free(p_max);
    }
    else if(p_max->next == NULL)
    {
        pp_max->next = NULL;
        free(p_max);
    }
    else
    {
        pp_max->next = p_max->next;
        free(p_max);
    }
    return head;
}
int main()
{
    //填补程序：模拟创建进程控制块队列，并按照优先级逐个出队过程
    node *head;
    head = creat();
    print(head);
    int count = 0;
    while(head)
    {
        count++;
        printf("第%d次出队的进程为：\n", count);
        head = processdo(head);
        printf("\n");
        print(head);
        system("pause");
    }
    return 0;
}
