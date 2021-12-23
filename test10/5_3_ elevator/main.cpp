#include <malloc.h>
#include<stdio.h>
#include<math.h>
#include <limits.h>
typedef struct track
{
    int column;
    struct track *next;
} node;
int location; /* ��ǰ��ͷλ��*/
int sum_move; /* ��ͷ�ƶ��ܴŵ���*/
float ave_move; /* ��ͷ�ƶ�ƽ���ŵ���*/
int direction; /* ��ͷ�ƶ��ķ���direction=1  ��ʾ���������ƶ���direction=-1  ��ʾ����
�����ƶ�*/
node *del;      //ɾ���Ľ��
node *found_node(node *head) /* �ҵ��뵱ǰ��ͷ������� direction  ͬ����Ĵŵ�*/
{
    //�����
    int min = 10000;
    node *p, *temp;
    p = head;
    temp = NULL;
    if(direction == 1)
    {
        while(p)
        {
            if((p->column > location) && ((p->column - location) < min))
            {
                temp = p;
                min = p->column - location;
            }
            p = p->next;
        }
    }
    else
    {
        while(p)
        {
            if((p->column < location) && ((location - p->column) < min))
            {
                temp = p;
                min = location - p->column;
            }
            p = p->next;
        }
    }
    return temp;
}
node *SCAN(node *head) /* ���� found_node  �ҵ����������Ĵŵ������� head  ������ɾ��
�ý��*/
{
    //�����
    del = found_node(head);
    if(!del)
    {
        direction = direction - 2 * direction;
        del = found_node(head);
    }
    node *p = head;
    while(p && p->next != del)
        p = p->next;
    if(p == head)
        head = head->next;
    else
        p->next = del->next;
    return head;
}
int main()
{
    int i,num,disk_length;
    node *head,*p,*pre;
    FILE *fp = fopen("date.txt", "r");
    printf("���������������:\n");
    //scanf("%d",&disk_length);
    fscanf(fp,"%d",&disk_length);
    printf("������̶�д��������:\n");
    //scanf("%d",&num);
    fscanf(fp,"%d",&num);
    printf("������̶�д�������������:\n");
    for(i=1; i<=num; i++)
    {
        //�����
        if(i == 1)
        {
            head = (node*)malloc(sizeof(node));
            //scanf("%d", &head->column);
            fscanf(fp,"%d", &head->column);
            p = head;
        }
        else
        {
            pre = (node*)malloc(sizeof(node));
            //scanf("%d", &pre->column);
            fscanf(fp,"%d", &pre->column);
            p->next = pre;
            p = pre;
        }
    }
    p->next = NULL;
    printf("������̵�ǰλ��Ϊ:\n");
    //scanf("%d",&location);
    fscanf(fp,"%d",&location);
    printf("��������ƶ�����(1 ��ʾ���������ƶ���-1 ��ʾ���������ƶ�):\n");
    fscanf(fp,"%d",&direction);
    fclose(fp);
    printf("\n ���η��ʵ������Ϊ:\n");
    sum_move=0;
    for(i=1; i<=num-1; i++)
    {
        //�����
        head = SCAN(head);
        printf("%5d", del->column);
        sum_move += abs(location - del->column);
        //printf("move=%d\n", abs(location - del->column));
        location = del->column;
    }
    ave_move=(float)sum_move/num;
    printf("\n �ܵ��ƶ��������Ϊ:%d\n ",sum_move);
    printf("\n ƽ���ƶ�����Ϊ��%.2f \n",ave_move);
    return 0;
}
