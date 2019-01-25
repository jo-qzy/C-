#include <iostream>
#include <pthread.h>
#include <queue>
#include <unistd.h>

typedef void (*HandleFunction)(void*);

void print(void* arg) {
    std::cout << *(int*)arg << std::endl;
}

class Task {
public:
    Task(HandleFunction ff){f = ff;}

    void operator()() {
        int i = 100;
        f((void*)&i);
    }
private:
    HandleFunction f;
};

class ThreadPool {
public:
    ThreadPool(int num = 5) {
        thread_nums = num;
        pthread_mutex_init(&lock, NULL);
        pthread_cond_init(&cond, NULL);
    }

    ~ThreadPool() {
        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&cond);
    }

    void InitThreadPool() {
        pthread_t tid;
        for (size_t i = 0; i < thread_nums; i++) {
            pthread_create(&tid, NULL, ThreadRotinue, this);
        }
    }

    static void *ThreadRotinue(void* arg) {
        pthread_detach(pthread_self());
        ThreadPool* tp = (ThreadPool*)arg;
        for (;;) {
            tp->LockQueue();
            while (tp->QueueIsEmpty()) {
                tp->ThreadIdle();
            }
            Task t = tp->GetTask();
            tp->TaskPop();
            tp->UnlockQueue();
            t();
        }
    }
    
    void TaskPush(Task& t) {
        LockQueue();
        task_queue.push(t);
        WakeUpThread();
        UnlockQueue();
    }
public:
    void LockQueue() {
        pthread_mutex_lock(&lock);
    }

    void UnlockQueue() {
        pthread_mutex_unlock(&lock);
    }

    void ThreadIdle() {
        idle_nums++;
        pthread_cond_wait(&cond, &lock);
        idle_nums--;
    }

    void WakeUpThread() {
        pthread_cond_signal(&cond);
    }

    bool QueueIsEmpty() {
        return task_queue.empty();
    }

    Task GetTask() {
        return task_queue.front();
    }

    void TaskPop() {
        task_queue.pop();
    }
private:
    int thread_nums;
    int idle_nums;
    std::queue<Task> task_queue;
    pthread_mutex_t lock;
    pthread_cond_t cond;
};

int main() {
    Task t(print);
    ThreadPool tp(5);
    tp.InitThreadPool();
    while (1){
        tp.TaskPush(t);
        sleep(1);
    }
    return 0;
}
