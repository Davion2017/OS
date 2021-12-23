#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define NULL 0
typedef struct processpcb
{
    int id; /* ���̿��ƿ���*/
    struct processpcb *next;
} node;
int n;
node *creat(void) /* �������̿��ƿ���б�*/
{
    //�����
    node *head, *p1, *p2;
    head = p1 = (node*)malloc(sizeof(node));
    p1->next = NULL;
    p2 = (node*)malloc(sizeof(node));
    scanf("%d", &p2->id);
    while(p2->id > 0)
    {
        if(head->next == NULL)
        {
            head->id = p2->id;
            head->next = p1;
        }
        else
        {
            p1->next = p2;
            p2->next = NULL;
            p1 = p2;
        }
        p2 = (node*)malloc(sizeof(node));
        scanf("%d", &p2->id);
    }
    return head;
}
node *append(node *head,node *q) /* ����һ�����̽������*/
{
    //�����
    node *p = head, *pre = NULL;
    while(p)
    {
        if(p->id == q->id)
        {
            printf("�����Ѵ��ڣ�\n");
            return head;
        }
        pre = p;
        p = p->next;
    }
    pre->next = q;
    q->next = NULL;
    return head;
}
void print (node *head) /* �������*/
{
    //�����
    node *p = head;
    while(p)
    {
        printf("%d\t", p->id);
        p = p->next;
    }
    printf("\n");
}
int main()
{
    //�����ģ�⽨�����̿��ƿ���к���ӹ���
    node *head, *p;
    printf("�������̶��У�");
    head = creat();
    print(head);
    printf("������һ�����̶��У�");
    p = (node*)malloc(sizeof(node));
    scanf("%d",&p->id);
    while(p->id > 0)
    {
        append(head, p);
        print(head);
        p = (node*)malloc(sizeof(node));
        printf("������һ�����̶��У�");
        scanf("%d",&p->id);
    }
    return 0;
}
