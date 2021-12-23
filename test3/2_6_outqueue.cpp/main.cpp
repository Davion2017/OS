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
node *del(node *head,int pcb) /* ���ݽ��� PCB  �� id  �ҵ���Ҫ���еĽ���*/
{
    //�����
    node *p = head, *pre = NULL;
    if(head->id == pcb)
    {
        head = head->next;
        free(p);
        return head;
    }
    while(p)
    {
        if(p->id == pcb)
        {
            pre->next = p->next;
            free(p);
            return head;
        }
        pre = p;
        p = p->next;
    }
    printf("���̲����ڣ�\n");
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
    //�����ģ�⽨�����̿��ƿ���кͳ��ӹ���
    int x;
    node *head;
    printf("�������̶��У�");
    head = creat();
    print(head);
    while(head)
    {
        printf("����Ҫ���еĽ��̣�");
        scanf("%d", &x);
        head = del(head, x);
        print(head);
    }
    return 0;
}
