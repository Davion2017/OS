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
int List[N]; // ��Ű�ȫ���е��±�����
void initial()
// ������ʼ״̬�������� Resource ��Max �� �� Allocation ���ټ���� Need ��Available ��
{
    FILE *fp;
    //if((fp=fopen("date.txt","r")) == NULL)
    if((fp=fopen("date.txt","r")) == NULL)//�򿪲������ɹ�
    {
        printf("�򲻿�\n");
    }
    //printf("Resource--����M����Դ��������\n");
    for(int i = 0; i < M; i++)
    {
        fscanf(fp, "%d", &Resource[i]);
        //scanf("%d", &Resource[i]);
    }
    //printf("Max--����N�����̷ֱ��M����Դ�������������\n");
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            fscanf(fp, "%d", &Max[i][j]);
            //scanf("%d", &Max[i][j]);
        }
    }
    //printf("Allocation--����N�����̻��M����Դ��������\n");
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
// �����ǰ��״̬��|Process |Max |Allocation |Need |Available |
{
    printf("״̬��\n");
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
// ����ͬʱ������������{ ��Finish[i]=false;  ��Need[i][j] ��Work[j]}�� �Ľ����±� i( �޸�Finish[i]=true) �����򷵻�-1 ��
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
//̬ �ж���ǰ״̬�Ƿ�Ϊ��ȫ״̬ ������ true �� �� false �����Ѱ�ȫ���е��±���� List[N] ���顣
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
// �����ȫ���б�|Process |Work |Need |Allocation |Work+Alloc |Finish |
{
    Work[0] = Available[0];
    Work[1] = Available[1];
    Work[2] = Available[2];
    printf("��ȫ���б����£�\n");
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
void reqresource(int i, int request[M])             // ��ʾ�� i  ���������� M  ����Դ request[M]
{
    bool flag;
    int j;
    //Step1:  �ж����� Request[j] ��Need[i][j]
    for(j = 0 ; j < M; j++)
    {
        if(request[j] > Need[i][j])
        {
            printf("����������������룺\n");
            return;
        }
    }
    //Step2:  �ж����� Request[j] ��Available[j]
    for(j = 0; j < M; j++)
    {
        if(request[j] > Available[j])
        {
            printf("�����㹻��Դ����%d�����̶�����\n", i);
            return;
        }
    }
    //Step3:  Ԥ�ȷ���
    for(j = 0; j < M; j++)
    {
        Available[j] -= request[j];
        Allocation[i][j] += request[j];
        Need[i][j] -= request[j];
    }
    //Step4: ����Ƿ�Ϊ��ȫ״̬
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
        printf("�����ڰ�ȫ���У� ���ǰ�ȫ״̬��\n");
    }
    else
    {
        printf("�ǰ�ȫ״̬������ɹ���\n");
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
        while(reqid>=0 && reqid<N) // ������� id  �Ƿ�Ϸ�
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
