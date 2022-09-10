#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NULL 0
typedef struct processpcb
 { int id;/*进程控制块编号*/
   struct processpcb *next;
 }node;
 int n; 
 node *creat(void)   /*建立进程控制块队列表*/
 { node *head,*p1,*p2;
   n=0;
   printf("Input processpcb table:ID\n");
   p1=p2=(node *)malloc(sizeof(node));
   scanf("%d",&p1->id);
   head=NULL;
   while (p1->id>0)
    {n=n+1;
     if (n==1) head=p1;
     else p2->next=p1;
     p2=p1;
     p1=(node *) malloc (sizeof(node));
     scanf("%d",&p1->id);
    }
   p2->next=NULL;
   return(head);
 }
node *append(node *head,node *q)  /*增加一个进程进入队列*/
  {
 }
 void print (node *head)  /*输出链表*/
 { 
 }
void main()
{
}
