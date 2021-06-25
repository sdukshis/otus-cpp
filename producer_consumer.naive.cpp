// Illustrates reader writer problem with naive solution (sleep and check)

#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

const int ntasks = 10;
const std::chrono::milliseconds task_process_time(100);
const std::chrono::milliseconds task_waiting_timeout(100);
const std::chrono::milliseconds task_prep_time(100);

void producer(int &task, bool &task_ready, std::mutex &mtx) {
    for (int task_id = 0; task_id < ntasks; ++task_id) {
        std::this_thread::sleep_for(task_prep_time);
        std::unique_lock lock{mtx};
        task = task_id;
        task_ready = true;
        while (task_ready) {
            lock.unlock();
            std::this_thread::sleep_for(task_waiting_timeout);
            lock.lock();
        }
    }
}

int wait_for_task(int &task, bool &task_ready, std::mutex &mtx) {
    std::unique_lock lock(mtx);
    while (!task_ready) {
        lock.unlock();
        std::this_thread::sleep_for(task_waiting_timeout);
        lock.lock();
    }
    int task_id = task;
    task_ready = false;
    lock.unlock();
    return task_id;
}

void consumer(int &task, bool &task_ready, std::mutex &mtx) {
    for (;;) {
        int task_id = wait_for_task(task, task_ready, mtx);
        std::this_thread::sleep_for(task_process_time);
        if (task_id == ntasks - 1) {
            break;
        }
    }
}

int main() {
    int task;
    bool task_ready = false;
    std::mutex mtx;

    std::chrono::time_point start = std::chrono::high_resolution_clock::now();
    std::thread consumer_thread(consumer, std::ref(task), std::ref(task_ready),
                                std::ref(mtx));
    std::thread producer_thread(producer, std::ref(task), std::ref(task_ready),
                                std::ref(mtx));

    producer_thread.join();
    consumer_thread.join();
    std::chrono::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed " << elapsed.count() << " seconds\n";
}