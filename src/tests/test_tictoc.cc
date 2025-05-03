#include "common/tt_test.h"
#include "common/tt_log.h"
#include "common/tt_tictoc.h"

#include <unistd.h>
#include <random>

TEST(tictoc, test) {
    TicToc t;

    sleep(1);

    LOG("test: ", t.Toc());
}

TEST(tictoc_auto, test) {
    TicTocAuto t("test");

    sleep(1);
}


TEST(tictoc_stats, test) {
    int cnt = 20;
    while(cnt--) {
        TICTOC_STATS("test");
        usleep(rand()%1000*1000);
    }
}
