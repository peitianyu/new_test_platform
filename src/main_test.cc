#include "common/tt_test.h"
#include "common/tt_backtrace.h"
#include "common/tt_flag.h"

int main(int argc, char** argv) {
    REGISTER_SEGFAULT_HANDLER;

    PARSE_FLAG(argc, argv);
    
    return RUN_ALL_TESTS();
}