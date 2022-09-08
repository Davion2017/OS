#include <malloc.h>
#include<stdio.h>
#include<math.h>
typedef struct track
{
    int column;
    struct track *next;
} node;
int location; /* 当前磁头位置*/
int sum_move; /* 磁头移动总磁道数*/
float ave_move; /* 磁头移动平均磁道数*/
node *del;       //要删除的结点
node *found_SSTF(node *head) /* 找到离当前磁头最近的磁道 ，并从 head  中删除该结点*/
{
    //填补程序
    int min;
    node *p, *pre, *temp;
    p = head;
    pre = NULL;
    temp = NULL;
    min = abs(location - p->column);
    while(p)
    {
        if(abs(location - p->column) < min)
        {
            temp = pre;
            min = abs(location - p->column);
        }
        pre = p;
        p = p->next;
    }
    if(!temp)
    {
        del = head;
        head = head->next;
    }
    else
    {
        del = temp->next;
        temp->next = temp->next->next;
    }
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
    fclose(fp);
    printf("\n 依次访问的柱面号为:\n");
    sum_move=0;
    for(i=1; i<=num; i++)
    {
        //填补程序
        head = found_SSTF(head);
        printf("%d\t", del->column);
        sum_move += abs(del->column - location);
        location = del->column;
    }
    ave_move=(float)sum_move/num;
    printf("\n 总的移动柱面次数为:%d\n ",sum_move);
    printf("\n 平均移动次数为：%.2f \n",ave_move);
    return 0;
}
