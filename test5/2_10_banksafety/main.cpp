#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define M 3
#define N 5
int Resource[M];
int Max[N][M];
int Allocation[N][M];
int Need[N][M];
int Available[M];
int Work[M];
bool Finish[N];
int List[N]; // 存放安全序列的下标序列
void initial()
// 创建初始状态：先输入 Resource 、Max 和 和 Allocation ，再计算出 Need 、Available 。
{
    FILE *fp;
    //if((fp=fopen("date.txt","r")) == NULL)
    if((fp=fopen("date.txt","r")) == NULL)//打开操作不成功
    {
        printf("打不开\n");
    }
    //printf("Resource--输入M种资源总数量：\n");
    for(int i = 0; i < M; i++)
    {
        fscanf(fp, "%d", &Resource[i]);
        //scanf("%d", &Resource[i]);
    }
    //printf("Max--输入N个进程分别对M种资源的最大需求量：\n");
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            fscanf(fp, "%d", &Max[i][j]);
            //scanf("%d", &Max[i][j]);
        }
    }
    //printf("Allocation--输入N个进程获得M种资源的数量：\n");
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            fscanf(fp, "%d", &Allocation[i][j]);
            //scanf("%d", &Allocation[i][j]);
        }
    }
    fclose(fp);
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
    for(int i = 0; i < M; i++)
        Available[i] = Resource[i];
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            Available[j]-=Allocation[i][j];
        }
    }
}
void printState()
// 输出当前的状态表|Process |Max |Allocation |Need |Available |
{
    printf("状态表：\n");
    printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n","Process", "Max", "Allocation", "Need", "Available");
    for(int i = 0; i < N; i++)
    {
        printf("|P%-11d|", i);
        for(int j = 0; j < M; j++)
        {
            printf("%4d", Max[i][j]);
        }
        printf("|");
        for(int j = 0; j < M; j++)
        {
            printf("%4d", Allocation[i][j]);
        }
        printf("|");
        for(int j = 0; j < M; j++)
        {
            printf("%4d", Need[i][j]);
        }
        printf("|");
        if(i == 0)
        {
            for(int j = 0; j < M; j++)
            {
                printf("%4d", Available[j]);
            }
        }
        else
            printf("\t\t ");
        printf("|");
        printf("\n");
    }
    printf("\n");
}
int isfinish()
// 返回同时满足两个条件{ ①Finish[i]=false;  ②Need[i][j] ≤Work[j]}标 的进程下标 i( 修改Finish[i]=true) ，否则返回-1 。
{
    int flag;
    for(int i = 0; i < N; i++)
    {
        flag = 0;
        for(int j = 0; j < M; j++)
        {
            if(Finish[i] == false && Need[i][j] <= Work[j])
                flag++;
        }
        if(flag == M)
            return i;
    }
    return -1;
}
bool issafe()
//态 判定当前状态是否为安全状态 （返回 true 或 或 false ），把安全序列的下标放入 List[N] 数组。
{
    int i, j = 0;
    Work[0] = Available[0];
    Work[1] = Available[1];
    Work[2] = Available[2];
    while(isfinish() != -1)
    {
        i = isfinish();
        Work[0] += Allocation[i][0];
        Work[1] += Allocation[i][1];
        Work[2] += Allocation[i][2];
        Finish[i] = true;
        List[j++] = i;
    }
    for(int i = 0; i < N; i++)
    {
        if(Finish[i] == false)
            return false;
    }
    return true;
}
void printList( )
// 输出安全序列表|Process |Work |Need |Allocation |Work+Alloc |Finish |
{
    Work[0] = Available[0];
    Work[1] = Available[1];
    Work[2] = Available[2];
    printf("安全序列表如下：\n");
    printf("|%-12s|%-12s|%-12s|%-12s|%-12s|%-12s|\n","Process", "Work", "Need", "Allocation", "Work+Alloc", "Finish");
    for(int i = 0; i < N; i++)
    {
        printf("|P%-11d|", List[i]);
        for(int j = 0; j < M; j++)
        {
            printf("%4d", Work[j]);
        }
        printf("|");
        for(int j = 0; j < M; j++)
        {
            printf("%4d", Need[List[i]][j]);
        }
        printf("|");
        for(int j = 0; j < M; j++)
        {
            printf("%4d", Allocation[List[i]][j]);
        }
        printf("|");
        for(int j = 0; j < M; j++)
        {
            printf("%4d", Work[j] + Allocation[List[i]][j]);
        }
        printf("|");
        printf("%12d", Finish[List[i]]);
        printf("|");
        printf("\n");
        Work[0] += Allocation[List[i]][0];
        Work[1] += Allocation[List[i]][1];
        Work[2] += Allocation[List[i]][2];
    }
    printf("\n");
}
void reqresource(int i, int request[M])             // 表示第 i  个进程请求 M  类资源 request[M]
{
    bool flag;
    int j;
    //Step1:  判断条件 Request[j] ≤Need[i][j]
    for(j = 0 ; j < M; j++)
    {
        if(request[j] > Need[i][j])
        {
            printf("输入错误！请重新输入：\n");
            return;
        }
    }
    //Step2:  判断条件 Request[j] ≤Available[j]
    for(j = 0; j < M; j++)
    {
        if(request[j] > Available[j])
        {
            printf("尚无足够资源，第%d个进程堵塞。\n", i);
            return;
        }
    }
    //Step3:  预先分配
    for(j = 0; j < M; j++)
    {
        Available[j] -= request[j];
        Allocation[i][j] += request[j];
        Need[i][j] -= request[j];
    }
    //Step4: 检测是否为安全状态
    for(j = 0; j < N; j++)
        Finish[j] = false;
    if(issafe() != true)
    {
        for(j = 0; j < M; j++)
        {
            Available[j] += request[j];
            Allocation[i][j] -= request[j];
            Need[i][j] += request[j];
        }
        printf("不存在安全序列， 不是安全状态。\n");
    }
    else
    {
        printf("是安全状态，分配成功！\n");
        printList();
    }
}
int main()
{
    int reqid=-1,j,req[M];
    initial();
    printState();
    if(issafe()==false)
    {
        printf("Initial state is unsafe!\n");
    }
    else
    {
        printf("\nInitial state is safe!\n");
        printList();
        printf("Input the id of request process:");
        scanf("%d",&reqid);
        while(reqid>=0 && reqid<N) // 输入进程 id  是否合法
        {
            printf("Input request resources:");
            for(j=0; j<M; j++)
            {
                scanf("%d",&req[j]);
            }
            reqresource(reqid, req);
            printState();
            printf("Input the id of request process:");
            scanf("%d",&reqid);
        }
    }
    return 0;
}
