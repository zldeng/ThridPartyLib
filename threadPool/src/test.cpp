/*
* Copyright (C) 2018 All rights reserved.
* file : test.cpp
* author : zldeng hitdzl@gmail.com
* date : 2018-08-08
* description : enjoy coding!
*/

#include <iostream>
#include <chrono>
#include "ThreadPool.h"
#include <random>

using namespace std;
using namespace Thread_Pool;

void thread_func(const int idx)
{
	//std::cout <<"func " << idx << endl;
	std::default_random_engine e(time(0));
	std::uniform_int_distribution<unsigned> u(1, 5);
	
	std::chrono::milliseconds timespan(u(e) * 1000);
	std::this_thread::sleep_for(timespan);


	fprintf(stderr,"thread_func %d done\n",idx);
}

int main()
{
	const int thread_cnt = 10;
	const int queue_cnt = 20;
	const string pool_name = "simpe_thread_pool";

	ThreadPool thread_pool(thread_cnt,queue_cnt,pool_name);
	
	thread_pool.start();

	for(auto i = 0;i < 50;i++)
	{
		auto task = std::bind(thread_func,i);

		thread_pool.addTask(task);
	}

	cerr << "add task done\n";
	thread_pool.stop();


	return 0;	
}

