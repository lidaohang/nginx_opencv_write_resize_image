#include "log.h"

Logs::Logs()
{	
}

Logs::~Logs()
{
}

static Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("log"));



Logs& Logs::instance()
{
	static Logs log;
	Logger root = Logger::getRoot();
	 try {
		PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("/usr/local/nginx/conf/log4cplus.properties"));
	 }catch(...) {
	    LOG4CPLUS_FATAL(root, "Exception occured...");
	 }
	

    return log;
}

void Logs::write_debug(const char* message)
{
	LOG4CPLUS_DEBUG(logger, message);
}

void Logs::write_error(const char* message)
{ 
	LOG4CPLUS_ERROR(logger, message);
}

void Logs::write_warn(const char* message)
{
	LOG4CPLUS_WARN(logger, message);
}

/*
string Log::get_execute_cost(const char * prefix, struct timeval * tve, struct timeval * tvs)
{
	string final(prefix);
	double span = tve->tv_sec-tvs->tv_sec + (tve->tv_usec-tvs->tv_usec)/1000000.0;
	char str[20];
	sprintf(str,"%.1f",span*1000);
	final.append(str);
	final.append((const char *)"ms");
	return final;
}
*/
