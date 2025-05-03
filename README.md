## 项目名

## 项目简介
本项目旨在提供一个功能完善、足够简洁的测试标准平台，便于对各类功能模块进行标准化测试, 调试，涵盖数据处理、配置管理、图形绘制、计时操作等多种类型测试，致力于为开发、调试和验证工作提供有力支持

## 项目特点
    - 代码足够简练, 控制所有模块代码在100行以内
    - 仅头文件, 便于迁移
    - 不断更新, 会根据使用需求不断更新

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
│   ├── test.csv
│   └── test.ini
├── output
│   └── new_test.csv
├── rebuild.sh
└── src
    ├── common
    │   ├── tt_backtrace.h
    │   ├── tt_csv.h
    │   ├── tt_defer.h
    │   ├── tt_flag.h
    │   ├── tt_ini.h
    │   ├── tt_log.h
    │   ├── tt_plot.h
    │   ├── tt_test.h
    │   ├── tt_tictoc.h
    │   └── tt_timer.h
    ├── main_test.cc
    └── tests
        ├── test_csv.cc
        ├── test_flag.cc
        ├── test_ini.cc
        ├── test_plot.cc
        ├── test_tictoc.cc
        └── test_timer.cc

5 directories, 23 files
```
## 测试
```
# just run
./rebuild.sh
```
## 输出结果
```
[ INFO     ] Available tests:
  [0] csv.test
  [1] flag.test
  [2] ini.test
  [3] plot_x.test
  [4] plot_xy.test
  [5] plot_xyz.test
  [6] plot_vectors.test
  [7] plot_grid.test
  [8] plot_refresh.test
  [9] plot_clear.test
  [10] tictoc.test
  [11] tictoc_auto.test
  [12] tictoc_stats.test
  [13] timer.test
  [q] exit
=> Please enter a number or press [q] to exit: 
[ RUN      ] csv.test
读取的 CSV 数据:
1 2 3 
4 5 6 
7 8 9 
新数据已写入 new_test.csv 文件
[     PASS ] csv.test (1 ms)
[=======================================================================]
[ RUN      ] flag.test
--port: 8080 (Server port)
--server_address: "localhost" (Server address)
--timeout: 30.0f (Request timeout in seconds)
port: 9090
server_address: 192.168.1.1
timeout: 60
--port: 9090 (Server port)
--server_address: 192.168.1.1 (Server address)
--timeout: 60.0 (Request timeout in seconds)
[     PASS ] flag.test (0 ms)
[=======================================================================]
[ RUN      ] ini.test
Application Name: My
Application Version: 1
Debug Mode: Enabled
Coordinates: 10 20 30 40 50 
[     PASS ] ini.test (0 ms)
[=======================================================================]
[ RUN      ] plot_x.test
[     PASS ] plot_x.test (3 ms)
[=======================================================================]
[ RUN      ] plot_xy.test
[     PASS ] plot_xy.test (0 ms)
[=======================================================================]
[ RUN      ] plot_xyz.test
[     PASS ] plot_xyz.test (0 ms)
[=======================================================================]
[ RUN      ] plot_vectors.test
[     PASS ] plot_vectors.test (0 ms)
[=======================================================================]
[ RUN      ] plot_grid.test
[     PASS ] plot_grid.test (0 ms)
[=======================================================================]
[ RUN      ] plot_refresh.test
qt.qpa.xcb: X server does not support XInput 2
failed to get the current screen resources
QStandardPaths: XDG_RUNTIME_DIR not set, defaulting to '/tmp/runtime-root'
qt.qpa.xcb: QXcbConnection: XCB error: 1 (BadRequest), sequence: 164, resource id: 90, major code: 130 (Unknown), minor code: 47
qt.qpa.xcb: QXcbConnection: XCB error: 170 (Unknown), sequence: 177, resource id: 90, major code: 146 (Unknown), minor code: 20
q
[     PASS ] plot_refresh.test (1972 ms)
[=======================================================================]
[ RUN      ] plot_clear.test
[     PASS ] plot_clear.test (1001 ms)
[=======================================================================]
[ RUN      ] tictoc.test
test: 1.00019
[     PASS ] tictoc.test (1000 ms)
[=======================================================================]
[ RUN      ] tictoc_auto.test
logtest cost: 1001.26 ms
[     PASS ] tictoc_auto.test (1001 ms)
[=======================================================================]
[ RUN      ] tictoc_stats.test
logtest stats - min: 383.642 ms, max: 383.642 ms, avg: 383.642 ms
logtest stats - min: 383.642 ms, max: 886.658 ms, avg: 635.15 ms
logtest stats - min: 383.642 ms, max: 886.658 ms, avg: 682.628 ms
logtest stats - min: 383.642 ms, max: 915.487 ms, avg: 740.843 ms
logtest stats - min: 383.642 ms, max: 915.487 ms, avg: 751.46 ms
logtest stats - min: 335.591 ms, max: 915.487 ms, avg: 682.148 ms
logtest stats - min: 335.591 ms, max: 915.487 ms, avg: 639.931 ms
logtest stats - min: 335.591 ms, max: 915.487 ms, avg: 621.566 ms
logtest stats - min: 335.591 ms, max: 915.487 ms, avg: 624.697 ms
logtest stats - min: 335.591 ms, max: 915.487 ms, avg: 604.389 ms
logtest stats - min: 335.591 ms, max: 915.487 ms, avg: 582.467 ms
logtest stats - min: 27.4514 ms, max: 915.487 ms, avg: 536.215 ms
logtest stats - min: 27.4514 ms, max: 915.487 ms, avg: 548.064 ms
logtest stats - min: 27.4514 ms, max: 915.487 ms, avg: 513.162 ms
logtest stats - min: 27.4514 ms, max: 915.487 ms, avg: 529.884 ms
logtest stats - min: 27.4514 ms, max: 926.793 ms, avg: 554.691 ms
logtest stats - min: 27.4514 ms, max: 926.793 ms, avg: 553.887 ms
logtest stats - min: 27.4514 ms, max: 926.793 ms, avg: 546.839 ms
logtest stats - min: 27.4514 ms, max: 926.793 ms, avg: 527.159 ms
logtest stats - min: 27.4514 ms, max: 926.793 ms, avg: 537.61 ms
[     PASS ] tictoc_stats.test (10755 ms)
[=======================================================================]
[ RUN      ] timer.test
PRINT INFO
PRINT INFO
^C
[     PASS ] timer.test (2825 ms)
[=======================================================================]
```