#ifndef __COMMON_PLOT_H__
#define __COMMON_PLOT_H__


#include <iostream>
#include <sstream>
#include <memory>
#include <cstdio>
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

    std::ostringstream& Oss() { return m_gp; }

    void Show() const {
        if (!m_pipe) {
            m_pipe.reset(popen("gnuplot -persist", "w"));
            if (!m_pipe) {
                std::cerr << "无法打开管道到Gnuplot" << std::endl;
                return;
            }
        }

        std::string script = m_gp.str();
        std::fprintf(m_pipe.get(), "%s", script.c_str());
        std::fflush(m_pipe.get());
    }

private:
    std::ostringstream m_gp;
    mutable std::unique_ptr<FILE, decltype(&pclose)> m_pipe{nullptr, pclose};

    PlotManage() {
        m_gp << "set mouse\n";
        m_gp << "set key left\n";
        m_gp << "bind 'q' 'exit'\n";
    }

    ~PlotManage() {}
};


template <typename... Args, typename O>
O & __print(O &out, Args&&... args) {
    auto a = {(out << std::forward<Args>(args), 0)...};
    (void)a;
    return out;
}

#define TYPE_POINTS "with points"
#define TYPE_DOTS   "with dots"
#define TYPE_LINES  "with lines"
#define TYPE_VECTOR "with vectors arrowstyle 1"
#define TYPE_MATRIX "matrix with image"

#define OSS() PlotManage::GetInstance().Oss()
#define INPUT_TYPE(type) "'-' " type ","
#define SET_VECTOR_TYPE()                   __print(OSS(), "set style arrow 1 head filled size screen 0.03,15,45 lt rgb 'blue'\n")

#define PLOT_SET_TITLE(title)               __print(OSS(), "set title '", title, "'\n")
#define PLOT_INPUT_TYPE(input_type, ...)    __print(OSS(), "plot ", input_type, __VA_ARGS__, "\n")
#define PLOT_DATA(data)                     __print(OSS(), data, "e\n");
#define PLOT_CLEAR()                        OSS().str(std::string()), __print(OSS(), "clear\n");
#define PLOT_SUBPLOTS(rows, cols)           __print(OSS(), "set multiplot layout ", rows, ",", cols, "\n")
#define PLOT_END_SUBPLOTS()                 __print(OSS(), "unset multiplot\n")
#define PLOT_SHOW()                         PlotManage::GetInstance().Show()

#define PLOT_GRID(data, ...) do {                                   \
    __print(OSS(), "set palette rgbformulae 33,13,10 \n");          \
    __print(OSS(), "set size ratio -1\n");                          \
    PLOT_INPUT_TYPE(INPUT_TYPE(TYPE_MATRIX), __VA_ARGS__);          \
    PLOT_DATA(data);                                                \
    PLOT_SHOW();                                                    \
}while(0)

#endif // __COMMON_PLOT_H__