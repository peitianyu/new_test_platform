# 如果没有build文件夹, 新建一个
if [ ! -d "build" ]; then
    mkdir build
fi

cd build && cmake -G Ninja .. && ninja 

./all_tests --port=9090 --server_address=192.168.1.1 --timeout=60.0

cd ..