// Find a problem in this code

#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <thread>
#include <vector>

#if defined(__linux__) || defined(__APPLE__)
const char *null = "/dev/null";
#elif defined(_WIN32)
const char *null = "NUL";
#else
#error platform not supportedd
#endif

void savefile_bg(const std::string &filename, const std::vector<char> &buffer) {
    std::ofstream out(filename);
    std::thread bg_task(
        [](const std::vector<char> &buffer, std::ofstream &out) {
            out.write(buffer.data(), buffer.size());
            out.close();
            std::clog << "File written\n";
        },
        std::cref(buffer), std::ref(out));
}

int main() {
    std::vector<char> buffer(10 * 4096 * 4096, 'A');
    savefile_bg(null, buffer);
    std::this_thread::sleep_for(std::chrono::seconds(5));
}