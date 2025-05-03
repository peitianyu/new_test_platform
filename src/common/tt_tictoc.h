#ifndef __TICTOC_H__
#define __TICTOC_H__

#include <chrono>
#include <iostream>
#include "tt_log.h"
#include "tt_defer.h"

class TicToc
{
public:
    TicToc() : start_(std::chrono::high_resolution_clock::now()) {}
    void Tic() { start_ = std::chrono::high_resolution_clock::now(); }
    double Toc() const {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::duration<double>>(end - start_).count();
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};

class TicTocAuto
{
public:
    TicTocAuto(const std::string& msg = "") : msg_(msg) { tictoc_.Tic(); }
    ~TicTocAuto() { LOG("log", msg_, " cost: ", tictoc_.Toc() * 1000, " ms"); }
private:
    std::string msg_;
    TicToc tictoc_;
};

class TicTocStats
{
public:
    TicTocStats(const std::string& name) 
        : name_(name), count_(0), total_duration_(0.0), avg_duration_(0.0), 
        min_duration_(std::numeric_limits<double>::max()), 
        max_duration_(std::numeric_limits<double>::lowest()) {}

    void Update(const TicToc& tictoc)
    {
        double duration = tictoc.Toc();
        count_++;
        total_duration_ += duration;
        avg_duration_ = total_duration_ / count_;

        min_duration_ = std::min(min_duration_, duration);
        max_duration_ = std::max(max_duration_, duration);

        LOG("log", name_, " stats - min: ", min_duration_ * 1000, " ms, max: ",  
             max_duration_ * 1000, " ms, avg: ", avg_duration_ * 1000, " ms");
    }
private:
    std::string name_;
    int count_;
    double total_duration_;
    double avg_duration_;
    double min_duration_;
    double max_duration_;
};

#define TICTOC_STATS(name)  static TicTocStats t(name); TicToc tic; defer [&]{ t.Update(tic);};

#endif // __TICTOC_H__