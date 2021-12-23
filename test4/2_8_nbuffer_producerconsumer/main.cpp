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
typedef struct _queue //队列结构体
{
    int data[SIZE];
    int front; // 指向队头的下标
    int rear; // 指向队尾的下标
} Queue;
struct data //信号量结构体
{
    sem_t empty; //记录空缓冲区个数
    sem_t full; //记录装满数据缓冲区个数
    Queue q; //缓冲仓库：队列
};
pthread_mutex_t mutex; //互斥锁
struct data sem;
int num1 = 0, num2 = 0;
int InitQueue (Queue *q) // 队列初始化
{
    if (q == NULL)
    {
        return FALSE;
    }
    q->front = 0;
    q->rear = 0;
    return TRUE;
}
int QueueEmpty (Queue *q) //判断空对情况
{
    if(q->front == q->rear)
        return TRUE;
    else
        return FALSE;
}
int QueueFull (Queue *q) //判断队满的情况
{
    if((q->front+SIZE)%SIZE == q->rear - 1)
        return TRUE;
    else
        return FALSE;

}
int DeQueue (Queue *q, int *x) //出队函数
{
    if(QueueEmpty(q))
        return FALSE;
    else
    {
        *x = q->data[q->rear++];
        return *x;
    }
}
int EnQueue (Queue *q, int x) //进队函数
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
        Sleep(rand()%100); //随机睡眠
        sem_wait(&sem.empty);//信号量的 P 操作
        pthread_mutex_lock(&mutex);//互斥锁上锁
        num1++;
        printf("Producer 生产了一条数据：%d\n 输入数据：", num1);
        scanf("%d", &x);
        EnQueue(&sem.q, x);
        pthread_mutex_unlock(&mutex);//互斥锁解锁
        sem_post(&sem.full);//信号量的 V 操作
    }
}
void* Consumer(void *arg)
{
    while(1)
    {
        int y;
        Sleep(3000);
        //Sleep(rand()%100); //随机睡眠
        sem_wait(&sem.full);//信号量的 P 操作
        pthread_mutex_lock(&mutex);//互斥锁上锁
        num2++;
        printf("Consumer 消费了一条数据: %d\n", num2);
        printf("消费数据: %d\n", DeQueue(&sem.q, &y));
        pthread_mutex_unlock(&mutex);//互斥锁解锁
        sem_post(&sem.empty);//信号量的 V 操作
    }
}
int main()
{
    sem_init(&sem.empty, 0, 10); //信号量初始化
    //（做多容纳 10 条消息，容纳了 10 条生产者将不会生产消息）
    sem_init(&sem.full, 0, 0);
    pthread_mutex_init(&mutex, NULL); //互斥锁初始化
    InitQueue(&(sem.q)); //队列初始化
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
