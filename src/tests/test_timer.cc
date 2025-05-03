#include "common/tt_test.h"
#include "common/tt_log.h"
#include "common/tt_timer.h"

TEST(timer, test) {
    Timer t([](){
        LOG_INFO("PRINT INFO");
    }, 1000);
}

