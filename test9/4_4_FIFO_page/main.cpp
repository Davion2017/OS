#define M 3 /*M  为系统分配给作业的主存页面数*/
#define N 20 /*N  为要装入作业的页面总数*/
#include <stdio.h>
bool found(int x,int a[M]) /* 以下函数判断第 i 个页面是否在内存*/
{
    //填补程序
    for(int i = 0; i < M; i++)
    {
        if(a[i] == x)
            return true;
    }
    return false;
}
int main()
{
    int a[M]; /* 存放已装入内存的页号序列*/
    int b[N]; /* 存放作业页号序列*/
    int c[N]; /* 存放被淘汰的页号序列*/
    int count = 0; /*count  为缺页总次数*/
    int c_count = 0;
    bool flag; /*flag  标识该页是否在内存*/
    FILE *fp;
    fp = fopen("data.txt", "r");
    printf("请输入作业序号：\n");
    for(int i = 0; i < N; i++)
        fscanf(fp, "%d", &b[i]);
        //scanf("%d", &b[i]);
    fclose(fp);
    for(int i = 0; i< N; i++)
        printf("%d ", b[i]);
    printf("\n");
    for(int i = 0; i < N; i++)
    {
        if(!found(b[i], a))
        {
            if(count < M)
            {
                a[count] = b[i];
            }
            else
            {
                c[c_count++] = a[0];
                for(int i = 0; i < M - 1; i++)
                    a[i] = a[i+1];
                a[M - 1] = b[i];
            }
            count++;
        }
    }
    float t = N;
    printf("发生缺页的次数为：%d\n", count);
    printf("缺页终端率=%.2f%%\n",count/t*100);
    printf("驻留内存的页号分别为：");
    for(int i = 0; i < M; i++)
        printf("%d, ", a[i]);
    printf("\n");
    printf("被淘汰的页号分别为：");
    for(int i = 0; i < c_count; i++)
        printf("%d, ", c[i]);
    return 0;
}
