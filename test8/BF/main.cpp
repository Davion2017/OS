#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define NULL 0
#define MAXSIZE 1024
typedef struct table
{
    int address; /* �洢������ʼ��ַ*/
    int length; /* �洢��������*/
    int flag; /* �洢������־��0  Ϊ���У�1  Ϊ����ҵռ��*/
    char name[10]; /*�� �� flag==1  ʱ�洢����ռ�ñ�־��ҵ��������洢�� nil*/
    struct table *next;
} node;
bool success; /* ����ɹ����ı�־*/
node *insert(node *head, node *news) /* ���ա���ַ������ʽ���� news  ������������Ӧλ��*/
{
    //�����
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
node *creat(FILE *fp) /* ���ݵ�ַ������ʽ�������������(flag==1) ����з�����(flag==0)*/
{
    //�����
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

//node *distribute(node *freehead, node *distributedhead, node *work)
/* �ڿ��з��������ҳ��״κ��� work  �ķ�����ͬʱ�޸Ŀ��з�����ͷ��������*/
/*
{
    //�����
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
    }
    if(p1 != NULL)
        distributedhead = insert(distributedhead, work);
    return NULL;
}
*/
node *distribute(node *freehead, node *distributedhead, node *work)
{
     node *p1 = freehead, *p2 = NULL;
     int x = MAXSIZE;
     while(p1 != NULL)
     {
         if((p1->length - work->length) < x && (p1->length - work->length) >= 0)
         {
             x = p1->length - work->length;
             p2 = p1;
         }
         p1 = p1->next;
     }
    if(p2 == NULL)
        printf("distributing is not successful!\n\n");
    else
    {
        printf("distributing is successful!\n\n");
        work->address = p2->address;
        p2->address += work->length;
        work->flag = 1;
        p2->length -= work->length;
        distributedhead = insert(distributedhead, work);
    }
    if(freehead->length == 0)
        *freehead = *freehead->next;
    else
    {
        p1 = freehead;
        p2 = NULL;
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
void print (node *head) /* �������*/
{
    //�����
    if(head == NULL)
    {
        printf("�ǿյ�");
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
        printf("�򲻿���");
    printf("The distributed table is:\n");
    dtable=creat(fp); /*dtable  �����ѷ��������*/
    print(dtable);
    printf("The free table is:\n");
    ftable=creat(fp); /*ftable  ����δ���������*/
    fclose(fp);
    print(ftable);
    /* ���� ģ����� �ڴ����� ����*/
    while(1)
    {
        //�����
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
