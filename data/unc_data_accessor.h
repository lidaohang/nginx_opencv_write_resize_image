#pragma once

#ifndef DIS_DATA_UNCDATAACCESSOR_H_
#define DIS_DATA_UNCDATAACCESSOR_H_

#include "../common/internal.h"
#include "../common/image_data_block.h"

using namespace std;

namespace dis{
	namespace data{
		//unc��ʽ��ȡ����Դ��Ϣ
		class UncDataAccessor{
			public:
				UncDataAccessor(void);
				~UncDataAccessor(void);
				/*UNC����Դ�ӿ� 
				  filename:�ļ�·������ 
				  rt����������Դ
				*/
				void fetch_image_data(string & filename,image_data_t * rt,const img_stat_t & imgStat);
				
				/*
				�ж��ļ��Ƿ����
				*/
				bool fileExists(string & filename);
		};
	}
}

#endif

