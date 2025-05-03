#include "common/tt_test.h"
#include "common/tt_plot.h"

TEST(plot_x, test) {
    std::vector<std::tuple<float>> data;
    for(int i = 0; i < 100; i++) data.push_back(100-i);

    PLOT_POINTS(data, STYLE_DOTS, "x_data");
}

TEST(plot_xy, test) {
    std::vector<std::tuple<float, float>> data;
    for(int i = 0; i < 100; i++) data.push_back({i, 100-i});

    PLOT_POINTS(data, STYLE_LINES, "xy_data");
}

TEST(plot_xyz, test) {
    std::vector<std::tuple<float, float, float>> data;
    for(int i = 0; i < 100; i++) data.push_back({i, i, i});

    PLOT_POINTS(data, STYLE_DOTS, "xyz_data");
}

#include <cmath>
TEST(plot_vectors, test) {
    std::vector<float> x_start(10), y_start(10), x_end(10), y_end(10);

    for (int i = 0; i < 10; i++) {
        x_start[i] = i;
        y_start[i] = 0.0f;
        x_end[i] = i + cos(i * 0.5f) * 0.5f;
        y_end[i] = sin(i * 0.5f) * 0.5f;
    }

    PLOT_VECTORS(x_start, y_start, x_end, y_end, "blue", "Vector Field");
}

TEST(plot_grid, test) {
    std::vector<std::vector<float>> grid;
    grid.resize(10);
    for(int i = 0; i < 10; i++){
        grid[i].resize(10);
        for(int j = 0; j < 10; j++)
            grid[i][j] = i/10.0;
    }
    
    PLOT_GRID(grid, 10, 10);
}


#define WHILE_Q_EXIT() char c; while(std::cin >> c && c != 'q')
TEST(plot_refresh, test) {
    std::vector<std::tuple<float, float>> data(100);
    for (int i = 0; i < 100; i++) std::get<0>(data[i]) = i;

    WHILE_Q_EXIT() {
        for(int i = 0; i < 100; i++) 
            std::get<1>(data[i]) = sin(std::get<0>(data[i]) / 10.0 + static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX));
        
        PLOT_POINTS(data, STYLE_LINES, "Random Sine Wave");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

#include<unistd.h>
TEST(plot_clear, test) {
    std::vector<std::tuple<float>> data;
    for(int i = 0; i < 100; i++) data.push_back(100-i);

    PLOT_POINTS(data, STYLE_DOTS, "x_data");

    sleep(1);
 
    PLOT_CLEAR();
}