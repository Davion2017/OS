#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define NULL 0
typedef struct table
 { int key;              /*进程ID号*/
   int sequence;         /*进程进入队列顺序号*/
   char message[10];     /*进程说明信息*/
   struct table *next;
 }node;
 node *creat(void) /*定义函数，建立进程链表*/
 { node *head;
   node *p1,*p2;
   int n=0;
   p1=p2=(node *)malloc(sizeof (node));
   scanf("%d %d",&p1->key,&p1->sequence);
   gets(p1->message);
   head=NULL;
   while (p1->key!=0)  /*输入0表示结束*/
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
 void print (node *head)  /*输出链表*/
 { node *p;
   printf("\n The table is:\n");
   p=head;
   while(p)
     { 
      printf("%d,%d,%s\n",p->key,p->sequence,p->message);
      p=p->next;
     }
  }
 
 node *fcfs(node *head) /*模拟就绪进程队列中最先进入进程(队首进程)出队*/
 { node *p;
   p=head;
   printf("key=%d,sequence=%d,message=%s\n",p->key,p->sequence,p->message);
   p=p->next;
  return(p);
 }

 void main()
 { int count=0;
   node *p,*q;
   printf("新建的进程控制表为:\nkey sequence message\n");
   p=creat();  /*输入进程控制表*/
   print(p);   /*输出原始进程控制表*/
   while(p)    /*模拟进程逐个被调度并进入CPU运行的过程*/
    {count++;
     printf("\n第%d次被调度的就绪进程为:\n",count);
     q=fcfs(p);
     p=q;
    }
 }
