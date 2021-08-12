#include "logic.h"

#include "logger.h"

static auto &&logger = Logger();

void foo() { logger.info("foo called"); }
