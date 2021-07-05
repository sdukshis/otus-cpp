// Lock-based threadsafe multiple-producer/multiple-consumer queue

#pragma once

#include <condition_variable>
#include <deque>
#include <mutex>
#include <queue>

template <class T, class Container = std::deque<T>> class threadsafe_queue {
    std::queue<T, Container> queue;
    mutable std::mutex mtx;
    std::condition_variable cv;

  public:
    threadsafe_queue() = default;
    ~threadsafe_queue() = default;
    threadsafe_queue(const threadsafe_queue &) = delete;
    threadsafe_queue(threadsafe_queue &&) = delete;
    threadsafe_queue &operator=(const threadsafe_queue &) = delete;
    threadsafe_queue &operator=(threadsafe_queue &&) = delete;

    void push(const T &value) {
        {
            std::lock_guard lock(mtx);
            queue.push(value);
        }
        cv.notify_one();
    }

    void wait_and_pop(T &result) {
        std::unique_lock lock(mtx);
        cv.wait(lock, [this]() { return !queue.empty(); });
        result = queue.front();
        queue.pop();
    }

    bool empty() const {
        std::lock_guard lock(mtx);
        return queue.empty();
    }
};
