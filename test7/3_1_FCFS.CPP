#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define NULL 0
typedef struct table
 { int key;              /*����ID��*/
   int sequence;         /*���̽������˳���*/
   char message[10];     /*����˵����Ϣ*/
   struct table *next;
 }node;
 node *creat(void) /*���庯����������������*/
 { node *head;
   node *p1,*p2;
   int n=0;
   p1=p2=(node *)malloc(sizeof (node));
   scanf("%d %d",&p1->key,&p1->sequence);
   gets(p1->message);
   head=NULL;
   while (p1->key!=0)  /*����0��ʾ����*/
     {
     n=n+1;
     if (n==1) head=p1;
     else p2->next=p1;
     p2=p1;
     p1=(node *) malloc(sizeof (node));
     scanf("%d %d",&p1->key,&p1->sequence);
     gets(p1->message);
   }
   p2->next=NULL;
   return(head);
 }
 void print (node *head)  /*�������*/
 { node *p;
   printf("\n The table is:\n");
   p=head;
   while(p)
     { 
      printf("%d,%d,%s\n",p->key,p->sequence,p->message);
      p=p->next;
     }
  }
 
 node *fcfs(node *head) /*ģ��������̶��������Ƚ������(���׽���)����*/
 { node *p;
   p=head;
   printf("key=%d,sequence=%d,message=%s\n",p->key,p->sequence,p->message);
   p=p->next;
  return(p);
 }

 void main()
 { int count=0;
   node *p,*q;
   printf("�½��Ľ��̿��Ʊ�Ϊ:\nkey sequence message\n");
   p=creat();  /*������̿��Ʊ�*/
   print(p);   /*���ԭʼ���̿��Ʊ�*/
   while(p)    /*ģ�������������Ȳ�����CPU���еĹ���*/
    {count++;
     printf("\n��%d�α����ȵľ�������Ϊ:\n",count);
     q=fcfs(p);
     p=q;
    }
 }