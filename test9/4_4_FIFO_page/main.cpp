#define M 3 /*M  Ϊϵͳ�������ҵ������ҳ����*/
#define N 20 /*N  ΪҪװ����ҵ��ҳ������*/
#include <stdio.h>
bool found(int x,int a[M]) /* ���º����жϵ� i ��ҳ���Ƿ����ڴ�*/
{
    //�����
    for(int i = 0; i < M; i++)
    {
        if(a[i] == x)
            return true;
    }
    return false;
}
int main()
{
    int a[M]; /* �����װ���ڴ��ҳ������*/
    int b[N]; /* �����ҵҳ������*/
    int c[N]; /* ��ű���̭��ҳ������*/
    int count = 0; /*count  Ϊȱҳ�ܴ���*/
    int c_count = 0;
    bool flag; /*flag  ��ʶ��ҳ�Ƿ����ڴ�*/
    FILE *fp;
    fp = fopen("data.txt", "r");
    printf("��������ҵ��ţ�\n");
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
    printf("����ȱҳ�Ĵ���Ϊ��%d\n", count);
    printf("ȱҳ�ն���=%.2f%%\n",count/t*100);
    printf("פ���ڴ��ҳ�ŷֱ�Ϊ��");
    for(int i = 0; i < M; i++)
        printf("%d, ", a[i]);
    printf("\n");
    printf("����̭��ҳ�ŷֱ�Ϊ��");
    for(int i = 0; i < c_count; i++)
        printf("%d, ", c[i]);
    return 0;
}
