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
        ├── test_bt.cc
        ├── test_csv.cc
        ├── test_flag.cc
        ├── test_ini.cc
        ├── test_plot.cc
        ├── test_tictoc.cc
        └── test_timer.cc

4 directories, 25 files
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
  [1] csv.test
  [2] flag.test
  [3] ini.test
  [4] plot_x.test
  [5] plot_xy.test
  [6] plot_xyz.test
  [7] plot_vectors.test
  [8] plot_grid.test
  [9] plot_refresh.test
  [10] plot_clear.test
  [11] tictoc.test
  [12] tictoc_auto.test
  [13] tictoc_stats.test
  [14] timer.test
  [q] exit
=> Please enter a number or press [q] to exit: 
[ RUN      ] bt.test
4
1
2
3
2
5
3
5
3
5
3
5
6
6
3
1
1
1
[     PASS ] bt.test (3003 ms)
[=======================================================================]
[ RUN      ] csv.test
读取的 CSV 数据:
1 2 3 
4 5 6 
7 8 9 
新数据已写入 new_test.csv 文件
[     PASS ] csv.test (0 ms)
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
[     PASS ] flag.test (1 ms)
[=======================================================================]
[ RUN      ] ini.test
Application Name: My
Application Version: 1
Debug Mode: Enabled
Coordinates: 10 20 30 40 50 
[     PASS ] ini.test (0 ms)
[=======================================================================]
[ RUN      ] plot_x.test
[     PASS ] plot_x.test (2 ms)
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
[     PASS ] plot_refresh.test (3041 ms)
[=======================================================================]
[ RUN      ] plot_clear.test
[     PASS ] plot_clear.test (1000 ms)
[=======================================================================]
[ RUN      ] tictoc.test
test: 1.00065
[     PASS ] tictoc.test (1001 ms)
[=======================================================================]
[ RUN      ] tictoc_auto.test
logtest cost: 1001 ms
[     PASS ] tictoc_auto.test (1001 ms)
[=======================================================================]
[ RUN      ] tictoc_stats.test
logtest stats - min: 383.317 ms, max: 383.317 ms, avg: 383.317 ms
logtest stats - min: 383.317 ms, max: 886.592 ms, avg: 634.955 ms
logtest stats - min: 383.317 ms, max: 886.592 ms, avg: 682.478 ms
logtest stats - min: 383.317 ms, max: 915.459 ms, avg: 740.723 ms
logtest stats - min: 383.317 ms, max: 915.459 ms, avg: 751.403 ms
logtest stats - min: 335.719 ms, max: 915.459 ms, avg: 682.123 ms
logtest stats - min: 335.719 ms, max: 915.459 ms, avg: 639.883 ms
logtest stats - min: 335.719 ms, max: 915.459 ms, avg: 621.466 ms
logtest stats - min: 335.719 ms, max: 915.459 ms, avg: 624.575 ms
logtest stats - min: 335.719 ms, max: 915.459 ms, avg: 604.243 ms
logtest stats - min: 335.719 ms, max: 915.459 ms, avg: 582.289 ms
logtest stats - min: 27.1624 ms, max: 915.459 ms, avg: 536.029 ms
logtest stats - min: 27.1624 ms, max: 915.459 ms, avg: 547.895 ms
logtest stats - min: 27.1624 ms, max: 915.459 ms, avg: 512.977 ms
logtest stats - min: 27.1624 ms, max: 915.459 ms, avg: 529.66 ms
logtest stats - min: 27.1624 ms, max: 926.809 ms, avg: 554.482 ms
logtest stats - min: 27.1624 ms, max: 926.809 ms, avg: 553.639 ms
logtest stats - min: 27.1624 ms, max: 926.809 ms, avg: 546.568 ms
logtest stats - min: 27.1624 ms, max: 926.809 ms, avg: 526.948 ms
logtest stats - min: 27.1624 ms, max: 926.809 ms, avg: 537.432 ms
[     PASS ] tictoc_stats.test (10750 ms)
[=======================================================================]
[ RUN      ] timer.test
PRINT INFO
PRINT INFO
^C
[     PASS ] timer.test (2919 ms)
[=======================================================================]
```