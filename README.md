## 项目名(tt_test)

## 项目简介
本项目旨在提供一个功能完善、足够简洁的测试标准平台，便于对各类功能模块进行标准化测试, 调试，涵盖数据处理、配置管理、图形绘制、计时操作等多种类型测试，致力于为开发、调试和验证工作提供有力支持

## 项目特点
    - 代码足够简练, 所有模块代码尽量在200行以内
    - 仅头文件, 便于迁移

## 安装环境
```
ubuntu 20.04
c++17
ninja
```
## 文件夹结构
```
.
├── CMakeLists.txt
├── README.md
├── data
│   ├── test.bt
│   ├── test.csv
│   └── test.ini
├── rebuild.sh
└── src
    ├── common
    │   ├── tt_backtrace.h
    │   ├── tt_bt.h
    │   ├── tt_coroutine.h
    │   ├── tt_csv.h
    │   ├── tt_defer.h
    │   ├── tt_enum_to_string.h
    │   ├── tt_flag.h
    │   ├── tt_ini.h
    │   ├── tt_log.h
    │   ├── tt_plot.h
    │   ├── tt_serialize.h
    │   ├── tt_test.h
    │   ├── tt_tictoc.h
    │   └── tt_timer.h
    ├── main_test.cc
    └── tests
        ├── test_bt.cc
        ├── test_coroutine.cc
        ├── test_csv.cc
        ├── test_enum_to_string.cc
        ├── test_flag.cc
        ├── test_ini.cc
        ├── test_plot.cc
        ├── test_serialize.cc
        ├── test_tictoc.cc
        └── test_timer.cc

4 directories, 31 files
```
## 测试
```
# just run
./rebuild.sh
```
## 输出结果
```
[ INFO     ] Available tests:
  [0] bt.test
  [1] coroutine.test
  [2] csv.test
  [3] enum_to_string.test
  [4] flag.test
  [5] ini.test
  [6] plot_x.test
  [7] plot_xy.test
  [8] plot_vectors.test
  [9] plot_grid.test
  [10] serialize.test
  [11] tictoc.test
  [12] tictoc_auto.test
  [13] tictoc_stats.test
  [14] timer.test
  [q] exit
=> Please enter a number or press [q] to exit: 
```