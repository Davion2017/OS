#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define NULL 0
typedef struct table
{
    int key; /* ���� ID  ��*/
    int priority; /* ������ֵ*/
    char message[10]; /* ����˵����Ϣ*/
    struct table *next;
} node;
node *insert(node *head,node *news)
{
    //�����
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
} /* ���½��̲��뵽�Ѿ�����Ķ����У��Խ��̱��������Ӵ�С����*/
node *creat(void) /* ���庯�������� insert  ���������ź���Ľ�������*/
{
    //�����
    node *head, *p;
    head = (node*)malloc(sizeof(node));
    p = (node*)malloc(sizeof(node));
    head = NULL;
    printf("�½��Ľ��̿��Ʊ�Ϊ��\nkey priority message\n");
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
void print (node *head) /* �������*/
{
    //�����
    printf("The table is:\n");
    node *p = head;
    while(p)
    {
        printf("%d, %d, %s\n", p->key, p->priority, p->message);
        p = p->next;
    }
    printf("\n");
}
void rank_out(node *head) /* ģ�ⰴ��������С���̷ּ����ӵĹ���*/
{
    //�����
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
    //�����ģ����̿��ƿ���а������ȼ�������ӹ���
    node *head;
    int count = 0;
    head = creat();
    print(head);
    while(head)
    {
        count++;
        printf("��%d�����ӽ���Ϊ��\n", count);
        rank_out(head);
    }
    return 0;
}
