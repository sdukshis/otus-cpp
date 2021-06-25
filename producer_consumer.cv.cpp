// Illustrates reader writer problem with naive solution (sleep and check)

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

const int ntasks = 10;
const std::chrono::milliseconds task_process_time(100);
const std::chrono::milliseconds task_prep_time(100);

void producer(int &task, bool &task_ready, std::mutex &mtx,
              std::condition_variable &cv) {
    for (int task_id = 0; task_id < ntasks; ++task_id) {
        std::this_thread::sleep_for(task_prep_time);
        {
            std::lock_guard lock{mtx};
            task = task_id;
            task_ready = true;
        }
        cv.notify_one();
    }
}

int wait_for_task(int &task, bool &task_ready, std::mutex &mtx,
                  std::condition_variable &cv) {
    std::unique_lock lock(mtx);
    cv.wait(lock, [&task_ready]() { return task_ready; });

    int task_id = task;
    task_ready = false;
    lock.unlock();
    return task_id;
}

void consumer(int &task, bool &task_ready, std::mutex &mtx,
              std::condition_variable &cv) {
    for (;;) {
        int task_id = wait_for_task(task, task_ready, mtx, cv);
        std::this_thread::sleep_for(task_process_time);
        if (task_id == ntasks - 1) { // checks if it is a last task
            break;
        }
    }
}

int main() {
    int task;
    bool task_ready = false;
    std::mutex mtx;
    std::condition_variable cv;

    std::chrono::time_point start = std::chrono::high_resolution_clock::now();
    std::thread consumer_thread(consumer, std::ref(task), std::ref(task_ready),
                                std::ref(mtx), std::ref(cv));
    std::thread producer_thread(producer, std::ref(task), std::ref(task_ready),
                                std::ref(mtx), std::ref(cv));

    producer_thread.join();
    consumer_thread.join();
    std::chrono::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed " << elapsed.count() << " seconds\n";
}