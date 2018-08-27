/*
 * Copyright (C) 2018 All rights reserved.
 * file : main.cpp
 * author : zldeng hitdzl@gmail.com
 * date : 2018-08-27
 * description : enjoy coding!
 */

#include <iostream>
#include <gflags/gflags.h>

using namespace std;

DEFINE_string(name, "dzl", "user name");
DEFINE_int32(age,30,"user default age");
DEFINE_bool(debug, true, "");

int main(int argc, char** argv)
{
	//gflags::ParseCommandLineFlags(&argc, &argv, false);
	gflags::ParseCommandLineFlags(&argc, &argv, true);

	cout << "argc= " << argc << endl;
	for(int i = 0; i<argc; ++i)
		cout << "argv[" << i << "]:" << argv[i] << endl;

	cout << "name = " << FLAGS_name << endl;
	cout << "age = " << FLAGS_age << endl;

	if (FLAGS_debug) {
		cout << "debug mode..." << endl;
	}
	else {
		cout << "nodebug mode...." << endl;
	}

	cout << "finish demo!" << endl;

	gflags::ShutDownCommandLineFlags();
	return 0;
}
