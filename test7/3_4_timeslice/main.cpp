#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define NULL 0
typedef struct table
{
    int key; /* 进程 ID  号*/
    int run_time; /* 进程 运行时间*/
    char message[10]; /* 进程说明信息*/
    struct table *next;
} node;
node *creat(void) /* 定义函数，输入 ID  号和 顺序号 ，按照输入次序建立进程链表*/
{
    //填补程序
    node *head, *p1, *p2;
    int n = 0;
    p1 = p2 = (node*)malloc(sizeof(node));
    scanf("%d", &p1->key);
    head = NULL;
    while(p1->key > 0)
    {
        n++;
        scanf("%d%s", &p1->run_time, &p1->message);
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
    if(head == NULL)
    {
        printf("distribute is over!");
        return;
    }
    node *p = head;
    printf("recent table is:\n");
    while(p)
    {
        printf("%d,%d, %s\n", p->key, p->run_time, p->message);
        p = p->next;
    }
    printf("\n");
}
node *insert(node *head,node *news) /* 将进程 news  插入到队列尾部*/
{
    //填补程序
    node *p = head;
    while(p->next)
        p = p->next;
    p->next = news;
    news->next = NULL;
    return head;
}
node *timeslice(node *head,int cpu_base_time)
/* 模拟时间片轮转调度过程: 队列首进程使用一个时间片的 CPU*/
{
    //填补程序
    node *p = head;
    if(head->run_time <= cpu_base_time)
    {
        printf("key=%d, run_time=%d, message=%s\n", p->key, p->run_time, p->message);
        head = head->next;
        free(p);
    }
    else
    {
        printf("key=%d, run_time=%d, message=%s\n", p->key, cpu_base_time, p->message);
        head = head->next;
        p->run_time-=2;
        head = insert(head, p);
    }
    printf("\n");
    return head;
}
int main()
{
    int count=0,cpu_base_time;
    node *p;
    printf("新建的进程控制表为:\nkey run_time message\n");
    p=creat(); /* 输入进程控制表*/
    print(p); /* 输出原始进程控制表*/
    printf("CPU 运行的单位时间片 cpu_base_time 为:\n");
    scanf("%d",&cpu_base_time);
    while(p) /* 模拟按单位时间片 进程 逐个被调度并进入 CPU  运行的过程*/
    {
        //填补程序
        count++;
        printf("第%d次被调度的就绪进程为:\n", count);
        p = timeslice(p, cpu_base_time);
        print(p);
    }
    return 0;
}
