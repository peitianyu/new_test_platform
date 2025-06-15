#include "common/tt_test.h"
#include "common/tt_coroutine.h"
#include <iostream>
#include <chrono>
#include <functional>

static coroutine::Channel<int> channel;

static std::string async_func1(int i, const std::string b)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	return b + std::to_string(i);
}


static void routine_func1()
{
	int i = channel.pop();
	std::cout << i << std::endl;

    i = channel.front();
    std::cout << "front: " << i << std::endl;
	
	i = channel.pop();
	std::cout << i << std::endl;
}

static void routine_func2(int i)
{
	std::cout << "20" << std::endl;
	coroutine::yield();
	
	std::cout << "21" << std::endl;

	//run function async
	//yield current routine if result not returned
	std::string str0 = coroutine::await(async_func1, 0, "async:");
	std::cout << str0 << std::endl;

	std::string str1 = coroutine::await(std::bind(async_func1, 1, "async:"));
	std::cout << str1 << std::endl;
}


//expected: 00, 01, 20, 02, 10, 03, 21, 04, 11, 05, async:0, async:1
static void thread_func()
{
	//create routine with callback like std::function<void()>
	coroutine::routine_t rt1 = coroutine::create(routine_func1);
	coroutine::routine_t rt2 = coroutine::create(std::bind(routine_func2, 2));
	
	std::cout << "--00" << std::endl;	
	coroutine::resume(rt1);

	std::cout << "--01" << std::endl;
	coroutine::resume(rt2);
	
	std::cout << "--02" << std::endl;
	channel.push(10);
	
	std::cout << "--03" << std::endl;
	coroutine::resume(rt2);
	
	std::cout << "--04" << std::endl;
	channel.push(11);
	
	std::cout << "--05" << std::endl;
	
	for (int i=0; i<400; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		coroutine::resume(rt2);
	}

	coroutine::destroy(rt1);
	coroutine::destroy(rt2);
}

TEST(coroutine, test) {
    std::thread t1(thread_func);
	std::thread t2([](){
		//coordinating routine does not support cross threading usage
	});
	t1.join();
	t2.join();
}