#include "common/tt_test.h"
#include "common/tt_log.h"
#include "common/tt_flag.h"

TEST(flag, test) {
    DEFINE_FLAG(int, port, 8080, "Server port");
    DEFINE_FLAG(std::string, server_address, "localhost", "Server address");
    DEFINE_FLAG(float, timeout, 30.0f, "Request timeout in seconds");

    PRINT_FLAGS();

    LOG("port: ", GET_FLAG(port, int));
    LOG("server_address: ", GET_FLAG(server_address, std::string));
    LOG("timeout: ", GET_FLAG(timeout, float));

    PRINT_FLAGS();
}

