#ifndef __COMMON_PLOT_H__
#define __COMMON_PLOT_H__

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <thread>
#include <chrono>
#include <sys/stat.h>
#include <stdexcept>
#include <tuple>
#include <type_traits>

class PlotManage {
public:
    static PlotManage& GetInstance() {
        static PlotManage instance;
        return instance;
    }

    PlotManage(const PlotManage&) = delete;
    PlotManage& operator=(const PlotManage&) = delete;

    void PlotSubplots(int rows, int cols) {
        std::fprintf(m_gp, "reset\n");
        std::fprintf(m_gp, "set multiplot layout %d,%d\n", rows, cols);
    }

    void PlotEndSubplots() {
        std::fprintf(m_gp, "unset multiplot\n");
    }

    template <typename... Args>
    void PlotPoints(const std::vector<std::tuple<Args...>>& data, const char* style = "points", const char* title = "Data") {
        std::fprintf(m_gp, "set title '%s'\n", title);
        if constexpr (sizeof...(Args) == 1) {
            std::fprintf(m_gp, "plot '-' w %s \n", style);
            for (const auto& point : data) std::fprintf(m_gp, "%f\n", std::get<0>(point));
        } else if constexpr (sizeof...(Args) == 2) {
            std::fprintf(m_gp, "plot '-' w %s \n", style);
            for (const auto& point : data) std::fprintf(m_gp, "%f %f\n", std::get<0>(point), std::get<1>(point));
        } else if constexpr (sizeof...(Args) == 3) {
            std::fprintf(m_gp, "splot '-' w %s \n", style);
            for (const auto& point : data) std::fprintf(m_gp, "%f %f %f\n", std::get<0>(point), std::get<1>(point), std::get<2>(point));
        }
        std::fprintf(m_gp, "e\n");
        std::fflush(m_gp);
    }

    void PlotVectors(const std::vector<float>& x_start, const std::vector<float>& y_start, 
        const std::vector<float>& x_end, const std::vector<float>& y_end, const char* color, const char* title = "Vectors") {
        std::fprintf(m_gp, "set title '%s' \n", title);
        std::fprintf(m_gp, "set style arrow 1 head filled size screen 0.03,15,45 lt rgb '%s'\n", color);
        std::fprintf(m_gp, "plot '-' with vectors arrowstyle 1 \n");
        for (size_t k = 0; k < x_start.size(); k++) 
            std::fprintf(m_gp, "%f %f %f %f\n", x_start[k], y_start[k], x_end[k], y_end[k]);
        std::fprintf(m_gp, "e\n");
        std::fflush(m_gp);
    }

    void PlotGrid(const std::vector<std::vector<float>> &grid, int width, int height, const char* title = "Grid") {
        std::fprintf(m_gp, "set title '%s' \n", title);
        std::fprintf(m_gp, "set view map \n");
        std::fprintf(m_gp, "set palette rgbformulae 33,13,10 \n");
        std::fprintf(m_gp, "plot '-' matrix with image \n");
        
        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) std::fprintf(m_gp, "%f ", grid[i][j]);
            std::fprintf(m_gp, "\n");
        }
        std::fprintf(m_gp, "e\n");
        std::fflush(m_gp);
    }

    void PlotClear() {
        std::fprintf(m_gp, "clear\n");
    }
private:
    FILE *m_gp;

    PlotManage() {
        m_gp = popen("gnuplot -persist", "w");
        std::fprintf(m_gp, "set mouse \n");
        std::fprintf(m_gp, "set key left \n");
        std::fprintf(m_gp, "bind 'q' 'exit'\n");
        std::fflush(m_gp);
    }

    ~PlotManage() { pclose(m_gp); }
};

#define STYLE_POINTS "points"
#define STYLE_LINES "lines"
#define STYLE_LINES_POINTS "linespoints"
#define STYLE_IMPULSES "impulses"
#define STYLE_DOTS "dots"
#define STYLE_BOXES "boxes"
#define STYLE_HISTOGRAM "histogram"
#define STYLE_IMAGE "image"
#define STYLE_VECTOR "vector"
#define STYLE_LABEL "label"
#define STYLE_COMMON "points pt 7 ps 1 lc rgb 'red'"

#define PLOT_CLEAR() PlotManage::GetInstance().PlotClear()
#define PLOT_POINTS(data, ...) PlotManage::GetInstance().PlotPoints(data, ##__VA_ARGS__)
#define PLOT_VECTORS(x_start, y_start, x_end, y_end, ...) PlotManage::GetInstance().PlotVectors(x_start, y_start, x_end, y_end, ##__VA_ARGS__)
#define PLOT_GRID(grid, width, height, ...) PlotManage::GetInstance().PlotGrid(grid, width, height, ##__VA_ARGS__)
#define PLOT_SUBPLOTS(rows, cols) PlotManage::GetInstance().PlotSubplots(rows, cols)
#define PLOT_END_SUBPLOTS() PlotManage::GetInstance().PlotEndSubplots()

#endif // __COMMON_PLOT_H__