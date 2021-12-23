#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Buff_MAX 10 // ��ʼ ���л������ĸ���
typedef struct buffernode
{
    int buf_type;
//"0" ���л�������"-1" װ�������ݵĻ�������"1" װ������ݵĻ�����
    int buf_data; // ѭ��������
    struct buffernode *next; // ָ����һ��ָ��
} node;
node *tempnode; // ȫ�ֱ���
/********************************************************************
create  ����˵��: �������л������, ÿ�����л������ڵ����ݴ�š�-32768 ����
����ֵ:  ���ض��е�ͷָ��
********************************************************************/
node *creat( ) /* �������л������*/
{
    //�����
    node *head, *p, *temp;
    head = (node*)malloc(sizeof(node));
    head->buf_data = -32768;
    head->buf_type = 0;
    head->next = NULL;
    p = head;
    int t = 9;
    while(t--)
    {
        temp = (node*)malloc(sizeof(node));
        temp->buf_data = -32768;
        temp->buf_type = 0;
        p->next = temp;
        p = temp;
    }
    p->next = NULL;
    return head;
}
/********************************************************************
print_buf  ����˵��: �ú�����ӡ ����������� ���������
����ֵ:  ��
********************************************************************/
void print_buf(node *emq, node *inq, node *outq)
{
    //�����
    node *p;
    printf("���л���������emq���ݣ�\n");
    p = emq;
    while(p)
    {
        printf("%d ", p->buf_data);
        p = p->next;
    }
    printf("\n\n");
    printf("���뻺��������inq���ݣ�\n");
    p = inq;
    if(p == NULL)
    {
        printf("Input buffer is empty.");
    }
    else
    {
        while(p)
        {
            printf("%d ", p->buf_data);
            p = p->next;
        }
    }
    printf("\n\n");
    printf("�������������outq���ݣ�\n");
    p = outq;
    if(p == NULL)
    {
        printf("Output buffer is empty.");
    }
    else
    {
        while(p)
        {
            printf("%d ", p->buf_data);
            p = p->next;
        }
    }
    printf("\n\n");
}
/********************************************************************
Getbuf  ����˵��: �� �ú����Ӷ��׶�һ�����ݳ����� ʹ�� tempnode  ָ����׵�һ�����
����ֵ: ����ָ�� head
********************************************************************/
node *Getbuf(node *head)
{
    //�����
    tempnode = head;
    head = head->next;
    return head;
}
/********************************************************************
Putbuf  ����˵��:  �ú� ���Ӳ���һ����㵽��δ��
����ֵ: ����ָ�� head
********************************************************************/
node *Putbuf(node *head, node *newnode)
{
    //�����
    node *p = head;
    if(head == NULL)
    {
        head = newnode;
        head->next = NULL;
    }
    else
    {
        while(p->next)
            p = p->next;
        newnode->next = NULL;
        p->next = newnode;
    }
    return head;
}
/**************MAIN  ����**********************/
int main(int argc, char *argv[])
{
    int flag;
    node *emq,*inq,*outq;
    node *hin,*sin,*sout,*hout;
    emq=creat();
    inq=NULL;
    outq=NULL;
    print_buf(emq,inq,outq);
    printf("\n######################\n");
    printf("what do you want to do?\n");
    printf("1. ��������\n");
    printf("2. �������\n");
    printf("3. �������\n");
    printf("4. ������\n");
    printf("5. �˳�\n");
    printf("\nInput your choice:");
    scanf("%d",&flag);
    while(flag !=5)
    {
        switch(flag)
        {
            //�����
        case 1:
                emq = Getbuf(emq);
                hin = tempnode;
                printf("��������--�����롰�������ݡ���");
                scanf("%d", &hin->buf_data);
                hin->buf_type = -1;
                inq = Putbuf(inq, hin);
                break;
        case 2:
                if(inq == NULL)
                {
                    printf("Input buffer is empty! Error!\n\n");
                }
                else
                {
                    inq = Getbuf(inq);
                    sin = tempnode;
                    printf("��ȡ����--�������ȡ���ݡ���%d\n", sin->buf_data);
                    sin->buf_type = 0;
                    sin->buf_data = -32768;
                    emq = Putbuf(emq, sin);
                }
                break;
        case 3:
                emq = Getbuf(emq);
                hout = tempnode;
                printf("��ȡ����--�����롰��ȡ���ݡ���\n");
                scanf("%d", &hout->buf_data);
                hout->buf_type = 1;
                outq = Putbuf(outq, hout);
                break;
        case 4:
                if(outq == NULL)
                {
                    printf("Output buffer is empty! Error!\n\n");
                }
                else
                {
                    outq = Getbuf(outq);
                    sout = tempnode;
                    printf("�������--�������ȡ���ݡ���%d\n", sout->buf_data);
                    sout->buf_data = -32768;
                    sout->buf_type = 0;
                    emq = Putbuf(emq, sout);
                }
                break;
        }
        printf("\n");
        print_buf(emq,inq,outq);
        printf("\n######################\n");
        printf("what do you want to do?\n");
        printf("1. ��������\n");
        printf("2. �������\n");
        printf("3. �������\n");
        printf("4. ������\n");
        printf("5. �˳�\n");
        printf("\nInput your choice:");
        scanf("%d",&flag);
    }
    return 0;
}
