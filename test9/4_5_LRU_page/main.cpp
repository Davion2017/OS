#define M 3 /*M  为系统分配给作业的主存页面数*/
#define N 20 /*N  为要装入作业的页面总数*/
#include <stdio.h>
int a[M]; /* 存放已装入内存的页号序列*/
int b[N]; /* 存放作业页号序列*/
int c[N]; /* 存放被淘汰的页号序列*/
int LRU(int pos) /* 分别调入页面 判断是否需要置换*/
{
    for(int i = 0; i < M; i++)
    {
        if(b[pos] == a[i])
        {
            for(int j = i; j < M - 1; j++)
                a[j] = a[j + 1];
            a[M - 1] = b[pos];
            return 0;
        }
    }
    return 1;
}
int main()
{
    FILE *fp;
    fp = fopen("data.txt", "r");
    printf("请输入作业序号：\n");
    for(int i = 0; i < N; i++)
        fscanf(fp, "%d", &b[i]);
    fclose(fp);
    for(int i = 0; i< N; i++)
        printf("%d ", b[i]);
    printf("\n");
    int count = 0; /*count  为缺页总次数*/
    int c_count = 0; //c_count  为淘汰分页次数
    for(int i = 0; i < N; i++)
    {
        if(count < M && LRU(i) == 1)
            a[count++] = b[i];
        else if(LRU(i) == 1)
        {
            c[c_count++] = a[0];
            for(int j = 0; j < M - 1; j++)
                a[j] = a[j + 1];
            a[M - 1] = b[i];
            count++;
        }
    }
    float t = N;
    printf("发生缺页的次数为：%d\n\n", count);
    printf("缺页终端率=%.2f%%\n\n",count/t*100);
    printf("驻留内存的页号分别为：");
    for(int i = 0; i < M; i++)
        printf("%d, ", a[i]);
    printf("\n\n");
    printf("被淘汰的页号分别为：");
    for(int i = 0; i < c_count; i++)
        printf("%d, ", c[i]);
    return 0;
}
