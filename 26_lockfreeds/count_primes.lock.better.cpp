// Count number of prime numbers less then input parameter

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <future>
#include <iostream>
#include <mutex>
#include <numeric>
#include <string>
#include <vector>

bool is_prime(int n) {
    if (n < 2) {
        return false;
    }

    for (int i = 2; i < n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int count_primes(int &n, std::mutex &mtx) {
    int count = 0;
    for (;;) {
        std::unique_lock lock(mtx);
        if (n == 1) {
            break;
        }
        int to_test = n--;
        lock.unlock();
        count += is_prime(to_test);
    }
    return count;
}

int main(int argc, char *argv[]) {
    using namespace std;
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " n [nthreads]\n";
        return EXIT_FAILURE;
    }
    int n = stoi(argv[1]);
    if (n <= 0) {
        cerr << "n must be positive number\n";
        return EXIT_FAILURE;
    }
    int n_threads = (argc > 2) ? stoi(argv[2]) : thread::hardware_concurrency();
    if (n_threads < 1) {
        cerr << "nthreads must be positive number\n";
        return EXIT_FAILURE;
    }

    vector<future<int>> tasks;
    std::mutex mtx;
    chrono::time_point start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n_threads; ++i) {
        tasks.emplace_back(
            async(std::launch::async, count_primes, ref(n), ref(mtx)));
    }

    size_t nprimes =
        transform_reduce(tasks.begin(), tasks.end(), 0, plus<int>{},
                         [](auto &result) { return result.get(); });
    chrono::time_point end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << nprimes << '\n';
    cout << "It tooks " << elapsed.count() << " seconds with " << n_threads
         << " threads\n";
}