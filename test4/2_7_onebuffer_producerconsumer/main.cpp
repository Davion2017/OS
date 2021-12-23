#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include <windows.h>
struct data //�ź����ṹ��
{
    sem_t empty; //��¼�ջ���������
    sem_t full; //��¼װ�����ݻ���������
    int buffer; //������
};
pthread_mutex_t mutex; //������
int num = 0; //��¼���������ݵĸ���
struct data sem;
void* Producer(void *arg)
{
    while(1)
    {
        Sleep(rand()%100); //���˯��
        sem_wait(&sem.empty);//�ź����� P ����
        pthread_mutex_lock(&mutex);//����������
        num++;
        printf("Producer ������һ�����ݣ�%d\n �������ݣ�", num);
        scanf("%d", &sem.buffer);
        pthread_mutex_unlock(&mutex);//����������
        sem_post(&sem.full);//�ź����� V ����
    }
}
void* Consumer(void *arg)
{
    while(1)
    {
        Sleep(rand()%100); //���˯��
        sem_wait(&sem.full);//�ź����� P ����
        pthread_mutex_lock(&mutex);//����������
        num--;
        printf("Consumer ������һ������: %d\n", num);
        printf("��������: %d\n", sem.buffer);
        pthread_mutex_unlock(&mutex);//����������
        sem_post(&sem.empty);//�ź����� V ����
    }
}
int main()
{
    sem_init(&sem.empty, 0, 1); //�ź�����ʼ��
    sem_init(&sem.full, 0, 0);
    pthread_mutex_init(&mutex, NULL); //��������ʼ��
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
