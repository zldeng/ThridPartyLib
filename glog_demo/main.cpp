/*
* Copyright (C) 2018 All rights reserved.
* file : main.cpp
* author : zldeng hitdzl@gmail.com
* date : 2018-07-09
* description : enjoy coding!
*/


#include <iostream>
#include <stdlib.h>
#include <cstring>

#include <glog/logging.h>

using namespace std;

int main(int argc,char** argv)
{
	const string log_dir = "./Log/";

	google::InitGoogleLogging(argv[0]);



	string info_log = log_dir + "master_info_";
	google::SetLogDestination(google::INFO,info_log.c_str());

	string warning_log = log_dir + "master_warning_";
	google::SetLogDestination(google::WARNING,warning_log.c_str());


	LOG(INFO) << "info hello world\n";

	LOG(WARNING) << "warning hello word\n";


	return 0;
}
