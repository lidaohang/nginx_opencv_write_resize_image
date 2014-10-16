#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/loggingmacros.h>



#include "internal.h"

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;



class Logs
{
public:
	
	void write_debug(const char* message);
	void write_error(const char* message);
	void write_warn(const char* message);
	/*
		获取执行时间字符串
	*/
	//string get_execute_cost(const char * prefix, struct timeval * tve, struct timeval * tvs);

	static Logs& instance();

public:
	Logs();
	~Logs();
};

