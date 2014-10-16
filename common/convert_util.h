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
		//����ת����
		class ConvertUtil
		{
		public:
			//��ʼ��һ��������
			static ConvertUtil* Instance()
			{
				static ConvertUtil* convertUtil;
				return convertUtil;
			}
			//intתstring
			string IntToString(int i);
			//stringתint
			int stringToInt(const string & str);
			//�ַ���ת��д
			void ToUpperString(string & str);
			//�ַ���ת��д
			void ToLowerString(string & str);
			//��ȡϵͳʱ���
			long getCurrentTime();
			//�����
			//long getRandom(long start, long end);
			//��ȡ�ļ�
			void fetch_file_data(string & fullpath,image_data_t * rt,const img_stat_t & imgStat);

			//url����
			//string urldecode(string &str_source);
			std::string deescapeURL(const std::string & url);
			std::string getErrorInfoJoint(string & errorInfo,int code);
			/*
				ʹ�÷ָ�������ַ���
			*/
			void splitStringByDelimiter(vector<string> & resultList, const string & source, const char & delimiter);
			//��ȡͼƬ�ļ���Ϣ
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

