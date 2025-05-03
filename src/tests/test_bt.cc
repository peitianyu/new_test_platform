#include "common/tt_test.h"
#include "common/tt_bt.h"

static int task4() { std::cout << "4" << std::endl; return 0; }
static int task5() { std::cout << "5" << std::endl; static int i = 3; return i--; }
static int task6() { std::cout << "6" << std::endl; static int i = -1; return i++ == 0; }

TEST(bt, test) {
    BtTree bt_tree;
    bt_tree.RegisterKeyword("task1", [](){ std::cout << "1" << std::endl; return 1; });
    bt_tree.RegisterKeyword("task2", [](){ std::cout << "2" << std::endl; return 1; });
    bt_tree.RegisterKeyword("task3", [](){ std::cout << "3" << std::endl; return 1; });
    bt_tree.RegisterKeyword("task4", task4);
    bt_tree.RegisterKeyword("task5", task5);
    bt_tree.RegisterKeyword("task6", task6);
    bt_tree.RunScript("../data/test.bt");
}

