#pragma once

#ifndef DIS_COMMON_CONVERTUTIL_H_
#define DIS_COMMON_CONVERTUTIL_H_

#include "internal.h"
#include <algorithm>
#include "image_data_block.h"

using namespace std;

namespace dis
{
	namespace common{ 
		//工具转化类
		class ConvertUtil
		{
		public:
			//初始化一个工具类
			static ConvertUtil* Instance()
			{
				static ConvertUtil* convertUtil;
				return convertUtil;
			}
			//int转string
			string IntToString(int i);
			//string转int
			int stringToInt(const string & str);
			//字符串转大写
			void ToUpperString(string & str);
			//字符串转大写
			void ToLowerString(string & str);
			//获取系统时间戳
			long getCurrentTime();
			//随机数
			//long getRandom(long start, long end);
			//读取文件
			void fetch_file_data(string & fullpath,image_data_t * rt,const img_stat_t & imgStat);

			//url解码
			//string urldecode(string &str_source);
			std::string deescapeURL(const std::string & url);
			std::string getErrorInfoJoint(string & errorInfo,int code);
			/*
				使用分隔符拆分字符串
			*/
			void splitStringByDelimiter(vector<string> & resultList, const string & source, const char & delimiter);
			//获取图片文件信息
			void statImage(const char* fileName, img_stat_t* imgStat);
			void statImage(image_data_t *data, img_stat_t* imgStat);
			
			int creatDir(char *pDir);

		private:
			ConvertUtil(void);
			~ConvertUtil(void);
		};
   }	
}

#endif 

