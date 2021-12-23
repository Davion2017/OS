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
node *creat(void) /* ���庯�������� ID  �ź����ȼ������������������������*/
{
    //�����
    int n = 0;
    node *head, *p1, *p2;
    printf("�½��Ľ��̿��Ʊ�Ϊ��\nkey priority message\n");
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
node *processdo(node *head) /* ģ�⵱ǰ������������̳��ӵĹ���*/
{
    //�����
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
    //�����ģ�ⴴ�����̿��ƿ���У����������ȼ�������ӹ���
    node *head;
    head = creat();
    print(head);
    int count = 0;
    while(head)
    {
        count++;
        printf("��%d�γ��ӵĽ���Ϊ��\n", count);
        head = processdo(head);
        printf("\n");
        print(head);
        system("pause");
    }
    return 0;
}
