#define M 3 /*M  Ϊϵͳ�������ҵ������ҳ����*/
#define N 20 /*N  ΪҪװ����ҵ��ҳ������*/
#include <stdio.h>
int a[M]; /* �����װ���ڴ��ҳ������*/
int b[N]; /* �����ҵҳ������*/
int c[N]; /* ��ű���̭��ҳ������*/
int LRU(int pos) /* �ֱ����ҳ�� �ж��Ƿ���Ҫ�û�*/
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
    printf("��������ҵ��ţ�\n");
    for(int i = 0; i < N; i++)
        fscanf(fp, "%d", &b[i]);
    fclose(fp);
    for(int i = 0; i< N; i++)
        printf("%d ", b[i]);
    printf("\n");
    int count = 0; /*count  Ϊȱҳ�ܴ���*/
    int c_count = 0; //c_count  Ϊ��̭��ҳ����
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
    printf("����ȱҳ�Ĵ���Ϊ��%d\n\n", count);
    printf("ȱҳ�ն���=%.2f%%\n\n",count/t*100);
    printf("פ���ڴ��ҳ�ŷֱ�Ϊ��");
    for(int i = 0; i < M; i++)
        printf("%d, ", a[i]);
    printf("\n\n");
    printf("����̭��ҳ�ŷֱ�Ϊ��");
    for(int i = 0; i < c_count; i++)
        printf("%d, ", c[i]);
    return 0;
}
