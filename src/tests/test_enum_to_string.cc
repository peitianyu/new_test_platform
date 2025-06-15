#include "common/tt_test.h"
#include "common/tt_log.h"
#include "common/tt_enum_to_string.h"

MAKE_ENUM(TestEnum,
    TEST_ENUM_1=0,
    TEST_ENUM_2,
    TEST_ENUM_3
);

TEST(enum_to_string, test) {
    TestEnum test_enum = TestEnum::TEST_ENUM_2;

    LOG("enum_to_string: ", enum_to_string(test_enum));    
}