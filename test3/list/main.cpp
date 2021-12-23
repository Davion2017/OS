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
node *append(node *head,node *q) /* ����һ�����̽������*/
{
    node * p = head;
    while(p)
        p = p->next;
    p->next = q;
    return head;
}
node *creat(void) /* �������̿��ƿ���б�*/
{
    node * head = (node*)malloc(sizeof(node));
    node * p;
    int x;
    scanf("%d", &x);
    while(x != 0)
    {
        p = (node*)malloc(sizeof(node));
        p->id = x;
        p->next = NULL;
        append(head, p);
        scanf("%d", &x);
    }
    return head;
}

void print (node *head) /* �������*/
{
    node * p;
    while(p)
    {
        printf("%d ", p->id);
        p = p->next;
    }
}
int main()
{
    node * head;
    head  = creat();
    print(head);
    return 0;
}
