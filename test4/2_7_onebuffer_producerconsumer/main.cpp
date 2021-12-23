#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include <windows.h>
struct data //信号量结构体
{
    sem_t empty; //记录空缓冲区个数
    sem_t full; //记录装满数据缓冲区个数
    int buffer; //缓冲区
};
pthread_mutex_t mutex; //互斥锁
int num = 0; //记录缓冲区数据的个数
struct data sem;
void* Producer(void *arg)
{
    while(1)
    {
        Sleep(rand()%100); //随机睡眠
        sem_wait(&sem.empty);//信号量的 P 操作
        pthread_mutex_lock(&mutex);//互斥锁上锁
        num++;
        printf("Producer 生产了一条数据：%d\n 输入数据：", num);
        scanf("%d", &sem.buffer);
        pthread_mutex_unlock(&mutex);//互斥锁解锁
        sem_post(&sem.full);//信号量的 V 操作
    }
}
void* Consumer(void *arg)
{
    while(1)
    {
        Sleep(rand()%100); //随机睡眠
        sem_wait(&sem.full);//信号量的 P 操作
        pthread_mutex_lock(&mutex);//互斥锁上锁
        num--;
        printf("Consumer 消费了一条数据: %d\n", num);
        printf("消费数据: %d\n", sem.buffer);
        pthread_mutex_unlock(&mutex);//互斥锁解锁
        sem_post(&sem.empty);//信号量的 V 操作
    }
}
int main()
{
    sem_init(&sem.empty, 0, 1); //信号量初始化
    sem_init(&sem.full, 0, 0);
    pthread_mutex_init(&mutex, NULL); //互斥锁初始化
    pthread_t producid;
    pthread_t consumid;
    pthread_create(&producid, NULL, Producer, NULL); //创建生产者线程
    pthread_create(&consumid, NULL, Consumer, NULL); //创建消费者线程
    pthread_join(consumid, NULL); //线程等待，如果没有这一步，主程序会直接结束，
    //导致线程也直接退出。
    sem_destroy(&sem.empty); //信号量的销毁
    sem_destroy(&sem.full);
    pthread_mutex_destroy(&mutex); //互斥锁的销毁
    return 0;
}
