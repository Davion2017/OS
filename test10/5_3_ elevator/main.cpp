#include <malloc.h>
#include<stdio.h>
#include<math.h>
#include <limits.h>
typedef struct track
{
    int column;
    struct track *next;
} node;
int location; /* 当前磁头位置*/
int sum_move; /* 磁头移动总磁道数*/
float ave_move; /* 磁头移动平均磁道数*/
int direction; /* 磁头移动的方向：direction=1  表示从里向外移动，direction=-1  表示从外
向里移动*/
node *del;      //删除的结点
node *found_node(node *head) /* 找到离当前磁头最近且与 direction  同方向的磁道*/
{
    //填补程序
    int min = 10000;
    node *p, *temp;
    p = head;
    temp = NULL;
    if(direction == 1)
    {
        while(p)
        {
            if((p->column > location) && ((p->column - location) < min))
            {
                temp = p;
                min = p->column - location;
            }
            p = p->next;
        }
    }
    else
    {
        while(p)
        {
            if((p->column < location) && ((location - p->column) < min))
            {
                temp = p;
                min = location - p->column;
            }
            p = p->next;
        }
    }
    return temp;
}
node *SCAN(node *head) /* 调用 found_node  找到满足条件的磁道，并从 head  链表中删除
该结点*/
{
    //填补程序
    del = found_node(head);
    if(!del)
    {
        direction = direction - 2 * direction;
        del = found_node(head);
    }
    node *p = head;
    while(p && p->next != del)
        p = p->next;
    if(p == head)
        head = head->next;
    else
        p->next = del->next;
    return head;
}
int main()
{
    int i,num,disk_length;
    node *head,*p,*pre;
    FILE *fp = fopen("date.txt", "r");
    printf("输入磁盘柱面总数:\n");
    //scanf("%d",&disk_length);
    fscanf(fp,"%d",&disk_length);
    printf("输入磁盘读写请求总数:\n");
    //scanf("%d",&num);
    fscanf(fp,"%d",&num);
    printf("输入磁盘读写请求柱面号序列:\n");
    for(i=1; i<=num; i++)
    {
        //填补程序
        if(i == 1)
        {
            head = (node*)malloc(sizeof(node));
            //scanf("%d", &head->column);
            fscanf(fp,"%d", &head->column);
            p = head;
        }
        else
        {
            pre = (node*)malloc(sizeof(node));
            //scanf("%d", &pre->column);
            fscanf(fp,"%d", &pre->column);
            p->next = pre;
            p = pre;
        }
    }
    p->next = NULL;
    printf("输入磁盘当前位置为:\n");
    //scanf("%d",&location);
    fscanf(fp,"%d",&location);
    printf("输入磁盘移动方向(1 表示从里向外移动，-1 表示从外向里移动):\n");
    fscanf(fp,"%d",&direction);
    fclose(fp);
    printf("\n 依次访问的柱面号为:\n");
    sum_move=0;
    for(i=1; i<=num-1; i++)
    {
        //填补程序
        head = SCAN(head);
        printf("%5d", del->column);
        sum_move += abs(location - del->column);
        //printf("move=%d\n", abs(location - del->column));
        location = del->column;
    }
    ave_move=(float)sum_move/num;
    printf("\n 总的移动柱面次数为:%d\n ",sum_move);
    printf("\n 平均移动次数为：%.2f \n",ave_move);
    return 0;
}
