#include "url_parser.h"
#include "../common/log.h"
#include "../common/convert_util.h"
#include "../rule/rule_matcher.h"
#include "../process/opencv_compress_picture.h"


using namespace dis::parser;
using namespace dis::common;
using namespace dis::rule;
using namespace dis::process;
using namespace std;

UrlParser::UrlParser(void)
{

}


UrlParser::~UrlParser(void)
{

}

//log
static Logs logger=Logs::instance();
//static  char* Root_Mapping ="";// "/tmp/image_data/";

void UrlParser::process(char * src_fullpath, char * des_fullpath, image_data_t * retval){
	if(src_fullpath == NULL || des_fullpath == NULL)
	{
		retval->code=NOT_FIND;
		retval->data=NULL;
		retval->len=strlen(FAILURE.c_str());
		logger.write_error("src_fullpath or des_fullpath is null");
		return;
	}
	logger.write_debug("Orginal src_fullpath:");
	logger.write_debug(src_fullpath);
	logger.write_debug("Orginal des_fullpath:");
	logger.write_debug(des_fullpath);

	//构建参数option对象
	 Operation *oper =NULL;
	 try{
		 oper = RuleMatcher::Instance()->getOperation(des_fullpath);
	 }
	 catch(...)
	 {
		retval->code=NOT_FIND;
		retval->data=NULL;
		retval->len=strlen(FAILURE.c_str());
		logger.write_error("Operation is error");
		return;
	 }
	logger.write_debug("Operation down");
	//判断缩放的尺寸
	if(oper->width<=0 || oper->height<=0)
	{
		retval->code=NOT_FIND;
		retval->data=NULL;
		retval->len=strlen(FAILURE.c_str());
		logger.write_error("image width height is zero");
		return;
	}

	logger.write_debug("image unc find begin");
	//源路径
	/*string finalUncName(Root_Mapping);
	finalUncName.append(src_fullpath);*/
	
	int src_len=strlen(src_fullpath);
	oper->source_path = (char*)malloc((src_len+1)*sizeof(char));
	memset(oper->source_path,0,(src_len+1)*sizeof(char));	
	strcpy(oper->source_path,src_fullpath);

	//写入的目标路径
	/*string finalTargetfullpath(Root_Mapping);
	finalTargetfullpath.append(des_fullpath);*/
	
	int des_num=strlen(des_fullpath);
	oper->target_path = (char*)malloc((des_num+1)*sizeof(char));
	memset(oper->target_path,0,(des_num+1)*sizeof(char));		
	strcpy(oper->target_path,des_fullpath); 

	logger.write_debug(oper->source_path);
	logger.write_debug(oper->target_path);

	//图片文件状态
	img_stat_t imgStat;
	 try{
		ConvertUtil::Instance()->statImage(oper->source_path,&imgStat);
	 }
	 catch(...)
	 {
		retval->code=NOT_FIND;
		retval->data=NULL;
		retval->len=strlen(FAILURE.c_str());
		logger.write_error("img_stat_t is error");
		return;
	 }
	if(!imgStat.exist){
		retval->code=NOT_FIND;
		retval->data=NULL;
		retval->len=strlen(FAILURE.c_str());
		logger.write_error("image is not exist");
		return;
	}
	
	//图片处理
	logger.write_debug("process image begin");

	OpenCvCompressPicture* opencvCommpress=new OpenCvCompressPicture();
	try{
		opencvCommpress->resizeImage(oper,retval);
	}
	catch(...)
	{
		retval->code=SERVER_INTERNAL_ERROR;
		retval->data=NULL;
		retval->len=strlen(FAILURE.c_str());
		logger.write_error("img_stat_t is error");
		return;
	}

	free(oper->source_path);
	free(oper->target_path);
	free(oper->dir);
	free(oper);
	
	
	delete opencvCommpress;
	opencvCommpress = NULL;
	logger.write_debug("process image down");
}







extern "C"

void nginx_module_invoke_url_parser(empty_struct * p,  char * src_fullpath,  char * des_fullpath, image_data_t * retval)
{
    UrlParser * urlParser = (UrlParser *)p;
	urlParser->process(src_fullpath, des_fullpath, retval);
}
