/*
* Copyright (C) 2018 All rights reserved.
* file : ThreadPool.h
* author : zldeng hitdzl@gmail.com
* date : 2018-08-08
* description : enjoy coding!
*/

#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <thread>
#include <mutex>
#include <functional>
#include <string>
#include <condition_variable>
#include <queue>
#include <memory>

#include "nocopyable.h"

namespace Thread_Pool
{
	class ThreadPool : public nocopyable
	{
		public:	
			typedef std::function<void()> Task;
		private:
			std::mutex _mutex;
			std::condition_variable _not_empty;
			std::condition_variable _not_full;

			std::string _name;
			std::vector<std::thread> _threads;
			std::queue<Task> _queue;

			size_t _numThreads; // thread cnt in threadpool
			size_t _maxQueueSize; //max size of task queue 
			bool _running;

			bool isFull();
			void runInThread();
			Task take();
		public:

			explicit ThreadPool(const int num_threads,
					const int max_queue_size,
					const std::string &name = "");

			~ThreadPool();


			void start(); // create threads

			void stop(); //stop run new task and waiting the running task finish
			
			bool addTask(const Task &t); //add task to task queue
	};

};

#endif
