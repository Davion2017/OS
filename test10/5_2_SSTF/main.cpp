#include <malloc.h>
#include<stdio.h>
#include<math.h>
typedef struct track
{
    int column;
    struct track *next;
} node;
int location; /* ��ǰ��ͷλ��*/
int sum_move; /* ��ͷ�ƶ��ܴŵ���*/
float ave_move; /* ��ͷ�ƶ�ƽ���ŵ���*/
node *del;       //Ҫɾ���Ľ��
node *found_SSTF(node *head) /* �ҵ��뵱ǰ��ͷ����Ĵŵ� ������ head  ��ɾ���ý��*/
{
    //�����
    int min;
    node *p, *pre, *temp;
    p = head;
    pre = NULL;
    temp = NULL;
    min = abs(location - p->column);
    while(p)
    {
        if(abs(location - p->column) < min)
        {
            temp = pre;
            min = abs(location - p->column);
        }
        pre = p;
        p = p->next;
    }
    if(!temp)
    {
        del = head;
        head = head->next;
    }
    else
    {
        del = temp->next;
        temp->next = temp->next->next;
    }
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
    fclose(fp);
    printf("\n ���η��ʵ������Ϊ:\n");
    sum_move=0;
    for(i=1; i<=num; i++)
    {
        //�����
        head = found_SSTF(head);
        printf("%d\t", del->column);
        sum_move += abs(del->column - location);
        location = del->column;
    }
    ave_move=(float)sum_move/num;
    printf("\n �ܵ��ƶ��������Ϊ:%d\n ",sum_move);
    printf("\n ƽ���ƶ�����Ϊ��%.2f \n",ave_move);
    return 0;
}
