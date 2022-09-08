#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Buff_MAX 10 // 初始 空闲缓冲区的个数
typedef struct buffernode
{
    int buf_type;
//"0" 空闲缓冲区，"-1" 装输入数据的缓冲区，"1" 装输出数据的缓冲区
    int buf_data; // 循环区数据
    struct buffernode *next; // 指向下一个指针
} node;
node *tempnode; // 全局变量
/********************************************************************
create  函数说明: 建立空闲缓冲队列, 每个空闲缓冲区内的数据存放“-32768 ”。
返回值:  返回队列的头指针
********************************************************************/
node *creat( ) /* 建立空闲缓冲队列*/
{
    //填补程序
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
print_buf  函数说明: 该函数打印 三个缓冲队列 的数据情况
返回值:  无
********************************************************************/
void print_buf(node *emq, node *inq, node *outq)
{
    //填补程序
    node *p;
    printf("空闲缓冲区队列emq内容：\n");
    p = emq;
    while(p)
    {
        printf("%d ", p->buf_data);
        p = p->next;
    }
    printf("\n\n");
    printf("输入缓冲区队列inq内容：\n");
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
    printf("输出缓冲区队列outq内容：\n");
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
Getbuf  函数说明: ， 该函数从队首读一个数据出来， 使用 tempnode  指向队首第一个结点
返回值: 队列指针 head
********************************************************************/
node *Getbuf(node *head)
{
    //填补程序
    tempnode = head;
    head = head->next;
    return head;
}
/********************************************************************
Putbuf  函数说明:  该函 数从插入一个结点到队未。
返回值: 队列指针 head
********************************************************************/
node *Putbuf(node *head, node *newnode)
{
    //填补程序
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
/**************MAIN  程序**********************/
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
    printf("1. 收容输入\n");
    printf("2. 提出输入\n");
    printf("3. 收容输出\n");
    printf("4. 提出输出\n");
    printf("5. 退出\n");
    printf("\nInput your choice:");
    scanf("%d",&flag);
    while(flag !=5)
    {
        switch(flag)
        {
            //填补程序
        case 1:
                emq = Getbuf(emq);
                hin = tempnode;
                printf("收容输入--请输入“输入数据”：");
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
                    printf("提取输入--输出“提取数据”：%d\n", sin->buf_data);
                    sin->buf_type = 0;
                    sin->buf_data = -32768;
                    emq = Putbuf(emq, sin);
                }
                break;
        case 3:
                emq = Getbuf(emq);
                hout = tempnode;
                printf("提取输入--请输入“提取数据”：\n");
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
                    printf("收容输出--输出“提取数据”：%d\n", sout->buf_data);
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
        printf("1. 收容输入\n");
        printf("2. 提出输入\n");
        printf("3. 收容输出\n");
        printf("4. 提出输出\n");
        printf("5. 退出\n");
        printf("\nInput your choice:");
        scanf("%d",&flag);
    }
    return 0;
}
