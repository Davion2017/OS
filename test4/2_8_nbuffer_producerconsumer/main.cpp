#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define TRUE 1
#define FALSE 0
#define SIZE 10
typedef int QueueData;
typedef struct _queue //���нṹ��
{
    int data[SIZE];
    int front; // ָ���ͷ���±�
    int rear; // ָ���β���±�
} Queue;
struct data //�ź����ṹ��
{
    sem_t empty; //��¼�ջ���������
    sem_t full; //��¼װ�����ݻ���������
    Queue q; //����ֿ⣺����
};
pthread_mutex_t mutex; //������
struct data sem;
int num1 = 0, num2 = 0;
int InitQueue (Queue *q) // ���г�ʼ��
{
    if (q == NULL)
    {
        return FALSE;
    }
    q->front = 0;
    q->rear = 0;
    return TRUE;
}
int QueueEmpty (Queue *q) //�жϿն����
{
    if(q->front == q->rear)
        return TRUE;
    else
        return FALSE;
}
int QueueFull (Queue *q) //�ж϶��������
{
    if((q->front+SIZE)%SIZE == q->rear - 1)
        return TRUE;
    else
        return FALSE;

}
int DeQueue (Queue *q, int *x) //���Ӻ���
{
    if(QueueEmpty(q))
        return FALSE;
    else
    {
        *x = q->data[q->rear++];
        return *x;
    }
}
int EnQueue (Queue *q, int x) //���Ӻ���
{
    if(QueueFull(q))
        return FALSE;
    else
    {
        q->data[++q->front] = x;
        return TRUE;
    }
}
void* Producer(void *arg)
{
    while(1)
    {
        int x;
        Sleep(rand()%100); //���˯��
        sem_wait(&sem.empty);//�ź����� P ����
        pthread_mutex_lock(&mutex);//����������
        num1++;
        printf("Producer ������һ�����ݣ�%d\n �������ݣ�", num1);
        scanf("%d", &x);
        EnQueue(&sem.q, x);
        pthread_mutex_unlock(&mutex);//����������
        sem_post(&sem.full);//�ź����� V ����
    }
}
void* Consumer(void *arg)
{
    while(1)
    {
        int y;
        Sleep(3000);
        //Sleep(rand()%100); //���˯��
        sem_wait(&sem.full);//�ź����� P ����
        pthread_mutex_lock(&mutex);//����������
        num2++;
        printf("Consumer ������һ������: %d\n", num2);
        printf("��������: %d\n", DeQueue(&sem.q, &y));
        pthread_mutex_unlock(&mutex);//����������
        sem_post(&sem.empty);//�ź����� V ����
    }
}
int main()
{
    sem_init(&sem.empty, 0, 10); //�ź�����ʼ��
    //���������� 10 ����Ϣ�������� 10 �������߽�����������Ϣ��
    sem_init(&sem.full, 0, 0);
    pthread_mutex_init(&mutex, NULL); //��������ʼ��
    InitQueue(&(sem.q)); //���г�ʼ��
    pthread_t producid;
    pthread_t consumid;
    pthread_create(&producid, NULL, Producer, NULL); //�����������߳�
    pthread_create(&consumid, NULL, Consumer, NULL); //�����������߳�
    pthread_join(consumid, NULL); //�̵߳ȴ������û����һ�����������ֱ�ӽ�����
    //�����߳�Ҳֱ���˳���
    sem_destroy(&sem.empty); //�ź���������
    sem_destroy(&sem.full);
    pthread_mutex_destroy(&mutex); //������������
    return 0;
}
