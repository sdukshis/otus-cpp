#include "logic.h"

#include "logger.h"

#include <chrono>
#include <future>
#include <vector>

static auto &&logger = Logger::getLogger();

void process();

void foo() {
    logger.info("foo called");
    process();
}

void process() {
    logger.info("process called");
    std::vector<std::future<void>> jobs;
    for (int i = 0; i < 5; ++i) {
        jobs.emplace_back(std::async(std::launch::async, [&]() {
            using namespace std::literals::chrono_literals;
            logger.info("Job started");
            std::this_thread::sleep_for(10ms);
            logger.info("Job finished");
        }));
    }
    for (auto &&job : jobs) {
        job.get();
    }
}
