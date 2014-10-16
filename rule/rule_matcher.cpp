#include "rule_matcher.h"
#include "../common/log.h"

using namespace dis::rule;
using namespace std;

//log
static Logs logger=Logs::instance();

Operation*  RuleMatcher::getOperation(string url)
{
	if(url.length()==0)
	{
		return NULL;
	}
	
	//int tmp_filename=url.find_last_of("\\");
	int tmp_filename=url.find_last_of("/");
	if(tmp_filename<=0)
	{
		return NULL;
	}
	string dir=url.substr(0,tmp_filename);
	logger.write_debug(dir.c_str());
	string filename=url.substr(tmp_filename+1);
	if(filename.length()==0)
	{
		return NULL;
	}
	logger.write_debug(filename.c_str());
	//Ëõ·ÅµÄ³ß´ç80x60
	int tmp_img_size=filename.find_first_of("_");
	if(tmp_img_size<=0)
	{
		return NULL;
	}
	string img_size=filename.substr(0,tmp_img_size);
	if(img_size.length()==0)
	{
		return NULL;
	}
	logger.write_debug(img_size.c_str());
	int tmp_size=img_size.find_first_of("x");
	if(tmp_size<=0)
	{
		return NULL;
	}
	int width=atoi(img_size.substr(0,tmp_size+1).c_str());
	int height=atoi(img_size.substr(tmp_size+1).c_str());


	Operation *oper;
	oper=(Operation *)malloc(sizeof(Operation));
	
	int dir_len=strlen(dir.c_str());
	oper->dir = (char*)malloc((dir_len+1)*sizeof(char));
	memset(oper->dir,0,(dir_len+1)*sizeof(char));		
	strcpy(oper->dir,dir.c_str()); 


	oper->width=width;
	oper->height=height;
	oper->quality=87;
	oper->cut_height=0;
	oper->cut_width=0;

	return oper;
}
