/*
* Copyright (C) 2018 All rights reserved.
* file : ThreadPool.cpp
* author : zldeng hitdzl@gmail.com
* date : 2018-08-08
* description : enjoy coding!
*/

#include "ThreadPool.h"
#include <cassert>
#include <iostream>

using namespace Thread_Pool;
using namespace std;

ThreadPool::ThreadPool(const int num_threads,
		const int max_queue_size,
		const string &name):_name(name),
		_numThreads(num_threads),
		_maxQueueSize(max_queue_size),
		_running(false)
{
}

ThreadPool::~ThreadPool()
{
	if (_running)
	{
		stop();
	}
}

void ThreadPool::start()
{
	assert(_threads.empty());

	_running = true;
	_threads.reserve(_numThreads);

	for(auto i = 0;i < _numThreads;i++)
	{
		_threads.push_back(thread(&ThreadPool::runInThread,this));
	}
}

void ThreadPool::stop()
{
	//make sure no more new task is added to the threadpool
	{
		unique_lock<mutex> lock(_mutex);
		_running = false;

		//unlock all thread
		_not_empty.notify_all();
		_not_full.notify_all();
	}

	//wait for all running thread finish
	for(auto& th : _threads)
	{
		th.join();
	}
}

bool ThreadPool::addTask(const Task &f)
{
	//ThreadPool is set to 0 size,just run the task
	if (_threads.empty())
	{
		f();

		return true;
	}
	else //add the task to queue
	{
		unique_lock<mutex> lock(_mutex);
		if (!_running)
		{
			return false;
		}

		while (isFull() && _running)
		{
			_not_full.wait(lock);
		}
		
		if (!_running)
		{
			return false;
		}

		assert(!isFull());

		_queue.push(f);
		_not_empty.notify_one();

		return true;
	}
}

ThreadPool::Task ThreadPool::take()
{
	unique_lock<mutex> lock(_mutex);

	while (_queue.empty() && _running)
	{
		_not_empty.wait(lock);
	}

	Task task;
	if (!_queue.empty())
	{
		task = _queue.front();
		_queue.pop();

		if (_maxQueueSize > 0)
		{
			_not_full.notify_one();
		}
	}

	return task;
}


bool ThreadPool::isFull()
{
	return _maxQueueSize > 0 && _queue.size() >= _maxQueueSize;
}

void ThreadPool::runInThread()
{
	try
	{
		while(_running || !_queue.empty())
		{
			Task task = take();

			if (task)
			{
				task();
			}
		}
	}
	catch(const exception &ex)
	{
		cout << "exception in " << _name << " ex: " << ex.what();
		abort();
	}
}





