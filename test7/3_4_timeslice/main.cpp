#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define NULL 0
typedef struct table
{
    int key; /* ���� ID  ��*/
    int run_time; /* ���� ����ʱ��*/
    char message[10]; /* ����˵����Ϣ*/
    struct table *next;
} node;
node *creat(void) /* ���庯�������� ID  �ź� ˳��� �����������������������*/
{
    //�����
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
void print (node *head) /* �������*/
{
    //�����
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
node *insert(node *head,node *news) /* ������ news  ���뵽����β��*/
{
    //�����
    node *p = head;
    while(p->next)
        p = p->next;
    p->next = news;
    news->next = NULL;
    return head;
}
node *timeslice(node *head,int cpu_base_time)
/* ģ��ʱ��Ƭ��ת���ȹ���: �����׽���ʹ��һ��ʱ��Ƭ�� CPU*/
{
    //�����
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
    printf("�½��Ľ��̿��Ʊ�Ϊ:\nkey run_time message\n");
    p=creat(); /* ������̿��Ʊ�*/
    print(p); /* ���ԭʼ���̿��Ʊ�*/
    printf("CPU ���еĵ�λʱ��Ƭ cpu_base_time Ϊ:\n");
    scanf("%d",&cpu_base_time);
    while(p) /* ģ�ⰴ��λʱ��Ƭ ���� ��������Ȳ����� CPU  ���еĹ���*/
    {
        //�����
        count++;
        printf("��%d�α����ȵľ�������Ϊ:\n", count);
        p = timeslice(p, cpu_base_time);
        print(p);
    }
    return 0;
}
