#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include <benchmark/benchmark.h>

#include "connection_pool.h"

void BM_ConnectionPool(benchmark::State &state) {
    ConnectionPool pool{"pm.filonovpv.name",
                        static_cast<size_t>(state.range(0))};
    for (auto _ : state) {
        std::vector<ConnectionPool::Connection> conns;
        for (int i = 0; i < state.range(1); ++i) {
            conns.emplace_back(pool.get_connection());
        }
        benchmark::DoNotOptimize(conns);
    }
}

BENCHMARK(BM_ConnectionPool)
    ->Args({0, 10})
    ->Args({1, 10})
    ->Args({5, 10})
    ->Args({10, 10});

BENCHMARK_MAIN();

// const std::string_view request = "GET / HTTP/1.1\r\n"
//                                  "Host: pm.filonovpv.name\r\n"
//                                  "Connection: Keep-Alive\r\n"
//                                  "\r\n";

// const size_t response_buffer_len = 1024;

// int main() {
//     ConnectionPool pool{"pm.filonovpv.name", 10};
//     std::array<char, response_buffer_len> buffer;

//     auto conn = pool.get_connection();
//     std::cout << request;
//     conn.write(request.data(), request.size());
//     size_t bytes_read = 0;
//     bytes_read = conn.read(buffer.data(), buffer.size());
//     std::cout.write(buffer.data(), bytes_read);
// }
