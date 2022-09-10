#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NULL 0
typedef struct table
{
    int address; /* 存储分区起始地址*/
    int length; /* 存储分区长度*/
    int flag; /* 存储分区标志，0  为空闲，1  为被作业占据*/
    char name[10]; /*当 当 flag==1  时存储分区占用标志作业名，否则存储空 nil*/
    struct table *next;
} node;
bool success; /* 分配成功与否的标志*/
node *insert(node *head, node *news) /* 按照“地址递增方式”将 news  结点插入链表相应位置*/
{
    //填补程序
    if(head->address > news->address)
    {
        news->next = head;
        head = news;
        return head;
    }
    else
    {
        node *p = head, *pre = NULL;
        while(p)
        {
            if(p->address > news->address)
            {
                news->next = p;
                pre->next = news;
                return head;
            }
            pre = p;
            p = p->next;
        }
        pre->next = news;
        news->next = NULL;
    }
    return head;
}
node *creat(FILE *fp) /* 根据地址递增方式建立分配分区表(flag==1) 或空闲分区表(flag==0)*/
{
    //填补程序
    node *head, *p;
    head = (node*)malloc(sizeof(node));
    printf("address length flag(0 or 1)\n");
    //scanf("%d%d%d", &head->address, &head->length, &head->flag);
    fscanf(fp, "%d%d%d", &head->address, &head->length, &head->flag);
    //printf("\tinput job_name:");
    //scanf("%s", &head->name);
    if(head->flag == 1)
        fscanf(fp, "%s", &head->name);
    else
        strcpy(head->name, "nil");
    head->next = NULL;
    p = (node*)malloc(sizeof(node));
    //scanf("%d%d%d", &p->address, &p->length, &p->flag);
    fscanf(fp, "%d%d%d", &p->address, &p->length, &p->flag);
    while(p->address > 0)
    {
        //printf("\tinput job_name:");
        //scanf("%s", &p->name);
        if(head->flag == 1)
            fscanf(fp, "%s", &p->name);
        else
            strcpy(p->name, "nil");
        //head = insert(head, p);
        insert(head, p);
        p = (node*)malloc(sizeof(node));
        //scanf("%d%d%d", &p->address, &p->length, &p->flag);
        fscanf(fp,"%d%d%d", &p->address, &p->length, &p->flag);
    }
    return head;
}
node *distribute(node *freehead, node *distributedhead, node *work)
/* 在空闲分区表中找出首次合适 work  的分区，同时修改空闲分区表和分配分区表*/
{
    //填补程序
    node *p1 = freehead;
    while(p1 != NULL && p1->length < work->length)
        p1 = p1->next;
    if(p1 == NULL)
        printf("distributing is not successful!\n\n");
    else
    {
        printf("distributing is successful!\n\n");
        work->address = p1->address;
        p1->address += work->length;
        work->flag = 1;
        p1->length -= work->length;
        distributedhead = insert(distributedhead, work);
    }
    if(freehead->length == 0)
        *freehead = *freehead->next;
    else
    {
        p1 = freehead;
        node *p2 = NULL;
        while(p1)
        {
            if(p1->length == 0)
            {
                p2->next = p1->next;
                free(p1);
                return NULL;
            }
            p2 = p1;
            p1 = p1->next;
        }
    }
    return NULL;
}
void print (node *head) /* 输出链表*/
{
    //填补程序
    if(head == NULL)
    {
        printf("是空的");
    }
    node *p = head;
    while(p)
    {
        printf("%d,%d,%d,%s\n", p->address, p->length, p->flag, p->name);
        p = p->next;
    }
    printf("\n");
}
int main()
{
    //int a;
    struct table *dtable,*ftable,*work;
    //char workn[10];
    FILE *fp;
    if((fp = fopen("data.txt", "r")) == NULL)
        printf("打不开！");
    printf("The distributed table is:\n");
    dtable=creat(fp); /*dtable  输入已分配情况表*/
    print(dtable);
    printf("The free table is:\n");
    ftable=creat(fp); /*ftable  输入未分配情况表*/
    fclose(fp);
    print(ftable);
    /* 以下 模拟逐个 内存申请 过程*/
    while(1)
    {
        //填补程序
        printf("==================================\n");
        work = (node*)malloc(sizeof(node));
        printf("The length of worked job is:");
        scanf("%d", &work->length);
        printf("The name of worked job is:");
        scanf("%s", &work->name);
        distribute(ftable, dtable, work);
        printf("The free table is:\n");
        print(ftable);
        printf("The distributed table is:\n");
        print(dtable);
    }
    return 0;
}
