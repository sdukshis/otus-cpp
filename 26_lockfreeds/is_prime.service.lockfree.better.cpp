// is prime service skeleton

#include <chrono>
#include <cstdlib>
#include <exception>
#include <future>
#include <iostream>
#include <random>
#include <thread>

#include "boost/lockfree/queue.hpp"

const int done = -1;
const int queue_capacity = 1024;

using queue = boost::lockfree::queue<int>;

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if ((n % 2 == 0) || (n % 3 == 0)) {
        return false;
    }
    for (int i = 5; i * i <= n; i += 6) {
        if ((n % i == 0) || (n % (i + 2) == 0)) {
            return false;
        }
    }
    return true;
}

int consumer(queue &task_queue) {
    int primes_found = 0;
    for (;;) {
        int task;
        if (!task_queue.pop(task)) {
            continue;
        }
        if (task == done) {
            break;
        }
        primes_found += is_prime(task);
    }
    return primes_found;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << "ntasks [nworkers]\n";
        return EXIT_FAILURE;
    }
    int ntasks = std::stoi(argv[1]);
    if (ntasks < 0) {
        std::cerr << "ntasks must be non negative number\n";
        return EXIT_FAILURE;
    }
    int nworkers =
        (argc < 3) ? std::thread::hardware_concurrency() : std::stoi(argv[2]);
    if (nworkers < 1) {
        std::cerr << "nworkers must be positive number\n";
        return EXIT_FAILURE;
    }

    queue task_queue(queue_capacity);
    std::vector<std::future<int>> consumers;
    for (int i = 0; i < nworkers; ++i) {
        consumers.emplace_back(
            std::async(std::launch::async, consumer, std::ref(task_queue)));
    }
    std::chrono::time_point start = std::chrono::high_resolution_clock::now();
    std::random_device rd;
    std::uniform_int_distribution<int> dist;
    for (int i = 0; i < ntasks; ++i) {
        task_queue.push(dist(rd));
    }
    for (int i = 0; i < nworkers; ++i) {
        task_queue.push(done);
    }

    size_t total_primes_found = transform_reduce(
        consumers.begin(), consumers.end(), 0, std::plus<int>{},
        [](auto &result) { return result.get(); });
    std::chrono::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Total primes found: " << total_primes_found << '\n';
    std::cout << "Throughtput: " << ntasks / elapsed.count()
              << " numbers/second\n";
}
