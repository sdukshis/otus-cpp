#include "logger.h"
#include "logic.h"

static auto &&logger = Logger();

int main() {
    logger.info("Application started");
    foo();
    logger.info("Application finishing");
}
