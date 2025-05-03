#include "common/tt_test.h"
#include "common/tt_csv.h"

TEST(csv, test) {
    auto data = CSV_READ(int, "../data/test.csv");
    
    std::cout << "读取的 CSV 数据:" << std::endl;
    for (const auto& row : data) {
        for (const auto& value : row) std::cout << value << " ";
        std::cout << std::endl;
    }

    std::vector<std::vector<int>> newData = {
        {10, 11, 12},
        {13, 14, 15},
        {16, 17, 18}
    };

    CSV_WRITE(int, newData, "../output/new_test.csv");
    std::cout << "新数据已写入 new_test.csv 文件" << std::endl;
}

