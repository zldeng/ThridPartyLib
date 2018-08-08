/*
 * Copyright (C) 2018 All rights reserved.
 * file : nocopyable.h
 * author : zldeng hitdzl@gmail.com
 * date : 2018-08-08
 * description : enjoy coding!
 */

#ifndef _NOCOPYABLE_H_
#define _NOCOPYABLE_H_
namespace Thread_Pool
{
	class nocopyable
	{
		private:
			nocopyable(const nocopyable&) = delete;
			nocopyable& operator=(const nocopyable&) = delete;

		public:
			nocopyable() = default;
			~nocopyable() = default;
	};
}

#endif
