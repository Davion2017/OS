#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define NULL 0
typedef struct table
{
    int address; /* �洢������ʼ��ַ*/
    int length; /* �洢��������*/
    int flag; /* �洢������־��0  Ϊ���У�1  Ϊ����ҵռ��*/
    char name[10]; /*�� �� flag==1  ʱ�洢����ռ�ñ�־��ҵ��������洢�� nil*/
    struct table *next;
} node;
node *work; /* ����һ��ȫ�ֱ��� work ����λ��Ҫ�ͷŵĽ��*/
char type; /* ����һ��ȫ�ֱ��� type */
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
    //printf("address length flag(0 or 1)\n");
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
/* �ڿ��з��������ҳ��״κ��� work  �ķ�����ͬʱ�޸Ŀ��з�����ͷ��������*/
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
node *found(node *distributedhead,char workn[10]) /* �����ѷ������Ҫ���յķ���λ��*/
{
    //�����
    node *p = distributedhead;
    node *pre  = NULL;
    while(p)
    {
        if(strcmp(p->name, workn) == 0)
        {
            printf("Ҫ���յķ������ڣ�\n");
            pre->next = p->next;
            return p;
        }
        pre = p;
        p = p->next;
    }
    printf("Ҫ���յķ��������ڣ�\n");
    return NULL;
}
node *release(node *freehead,node *work) /* �����������ɿ��з������չ���*/
{
    //�����
    if(work == NULL)
        return NULL;
    node *p = freehead;
    node *pre = NULL;
    while(p != NULL && p->address < work->address)
    {
        pre = p;
        p = p->next;
    }
    if(pre == NULL)
    {
        if(work->address + work->length == p->address)
        {
            p->address = work->address;
            p->length+=work->length;
            type = 'B';
        }
        else
        {
            work->flag = 0;
            strcpy(work->name, "nil");
            work->next = freehead;
            freehead = work;
            type = 'D';
        }
    }
    else if(p == NULL)
    {
        if(pre->address + pre->length == work->address)
        {
            pre->length+=work->length;
            type = 'A';
        }
        else
        {
            work->next = NULL;
            work->flag = 0;
            strcpy(work->name, "nil");
            pre->next = p;
            type = 'D';
        }
    }
    else if((pre->address + pre->length) == work->address)   //��������
    {
        if((work->address + work->length) == p->address)    //���¶����� C
        {
            pre->length = pre->length + work->length + p->length;
            pre->next = p->next;
            free(p);
            type = 'C';
        }
        else                        //�����²��� A
        {
            pre->length += work->length;
            type = 'A';
        }
    }
    else           //�ϲ���
    {
        if((work->address + work->length) == p->address)    //�ϲ������� B
        {
            p->length += work->length;
            p->address = work->address;
            type = 'B';
        }
        else            //���¶����� D
        {
            work->flag = 0;
            strcpy(work->name, "nil");
            work->next = p;
            pre->next = work;
            type = 'D';
        }
    }
    printf("\nThe type of release is %c!\n\n", type);
    return freehead;
}
void print (node *head) /* �������*/
{
    //�����
    if(head == NULL)
    {
        printf("�ǿյ�");
    }
    node *p = head;
    printf("%s\t%s\t%s\t%s\n", "address", "length", "flag", "name");
    while(p)
    {
        printf("%d\t%d\t%d\t%s\n", p->address, p->length, p->flag, p->name);
        p = p->next;
    }
    printf("\n");
}
int main()
{
    int i = 0, sum;
    struct table *dtable,*ftable;
    char workn[10];
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
    printf("Input the released work segment sum:");
    scanf("%d", &sum);
    while(i < sum)
    {
        printf("===============================================\n");
        i++;
        printf("%d��input the released work segment name:", i);
        scanf("%s", workn);
        work = found(dtable, workn);
        ftable = release(ftable, work);
        printf("The distributed table is:\n");
        print(dtable);
        printf("The free table is:\n");
        print(ftable);
    }
    return 0;
}
