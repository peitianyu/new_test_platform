#include "common/tt_test.h"
#include "common/tt_plot.h"

TEST(plot_x, test) {
    std::string data_str;
    for(int i = 0; i < 100; i++) 
        data_str += std::to_string(100-i), data_str+="\n";

    PLOT_INPUT_TYPE(INPUT_TYPE(TYPE_DOTS), "");
    PLOT_DATA(data_str);
    PLOT_SHOW();
}

TEST(plot_xy, test) {
    std::string data_str;
    for(int i = 0; i < 100; i++) 
        data_str += std::to_string(100-i), data_str+=" ", std::to_string(i), data_str+="\n"; 

    PLOT_INPUT_TYPE(INPUT_TYPE(TYPE_POINTS), "");
    PLOT_DATA(data_str);
    PLOT_SHOW();
}

#include <cmath>
TEST(plot_vectors, test) {
    std::string data_str;
    for (int i = 0; i < 10; i++) {
        data_str += std::to_string(i), data_str+=" ";
        data_str += std::to_string(0), data_str+=" ";
        data_str += std::to_string(i + cos(i * 0.5f) * 0.5f), data_str+=" ";
        data_str += std::to_string(sin(i * 0.5f) * 0.5f), data_str+="\n";
    }

    SET_VECTOR_TYPE();
    PLOT_INPUT_TYPE(INPUT_TYPE(TYPE_VECTOR), "");
    PLOT_DATA(data_str);
    PLOT_SHOW();
}

TEST(plot_grid, test) {
    std::string grid =  "0 0 3 0 3 0 3 0 3 0 \n"
                        "3 0 3 0 3 0 3 0 3 0 \n"
                        "0 0 0 0 0 0 3 0 3 0 \n"
                        "0 0 0 0 0 0 3 0 3 0 \n"
                        "0 0 3 0 0 0 3 0 3 0 \n"
                        "3 0 3 0 0 0 3 0 3 0 \n"
                        "0 0 3 0 3 0 3 0 3 0 \n"
                        "0 0 3 0 3 0 3 0 3 0 \n"
                        "0 0 3 0 3 0 3 0 3 0 \n"
                        "3 0 0 0 3 0 3 0 3 0 \n";
    
    PLOT_GRID(grid, " ");
}

