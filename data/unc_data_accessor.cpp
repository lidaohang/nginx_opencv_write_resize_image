#include "unc_data_accessor.h"
#include "../common/log.h"
#include "../common/internal.h"
#include "../common/convert_util.h"

using namespace dis::data;
using namespace dis::common;

UncDataAccessor::UncDataAccessor(void)
{
}
UncDataAccessor::~UncDataAccessor(void)
{
}

//log
static Logs logger=Logs::instance();

/*获取UNC数据源接口 
  filename:文件路径名称 
  rt：返回数据源
*/
void UncDataAccessor::fetch_image_data(string & fullpath,image_data_t * rt,const img_stat_t & imgStat){
	//struct timeval tvs,tve;
	//gettimeofday(&tvs,NULL);
	logger.write_debug("UNC Path is:");
	logger.write_debug(fullpath.c_str());

	dis::common::ConvertUtil::Instance()->fetch_file_data(fullpath,rt,imgStat);

	//构建并记录时间花销
	//gettimeofday(&tve,NULL);
	//string str =logger.get_execute_cost("#####Data access by UNC Cost: ", &tve, &tvs);
	//logger.write_debug(str.c_str());
}


/*
判断文件是否存在
*/
bool UncDataAccessor::fileExists(string & filename)
{
	//struct timeval tvs,tve;
	//gettimeofday(&tvs,NULL);
	logger.write_debug("UNC Path is:");
	logger.write_debug(filename.c_str());	

	FILE *fp  = fopen(filename.c_str(),"rb");
	//如果读取的文件不存在
	if(fp == NULL){
		logger.write_error("File not exists, File-Path is");
		logger.write_error(filename.c_str());
		return false;
	}	

	//构建并记录时间花销
	//gettimeofday(&tve,NULL);
	//string str =logger.get_execute_cost("#####Check file exists Cost: ", &tve, &tvs);
	//logger.write_debug(str.c_str());
	fclose(fp);
	return true;
}