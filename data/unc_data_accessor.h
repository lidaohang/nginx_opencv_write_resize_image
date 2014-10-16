#pragma once

#ifndef DIS_DATA_UNCDATAACCESSOR_H_
#define DIS_DATA_UNCDATAACCESSOR_H_

#include "../common/internal.h"
#include "../common/image_data_block.h"

using namespace std;

namespace dis{
	namespace data{
		//unc方式获取数据源信息
		class UncDataAccessor{
			public:
				UncDataAccessor(void);
				~UncDataAccessor(void);
				/*UNC数据源接口 
				  filename:文件路径名称 
				  rt：返回数据源
				*/
				void fetch_image_data(string & filename,image_data_t * rt,const img_stat_t & imgStat);
				
				/*
				判断文件是否存在
				*/
				bool fileExists(string & filename);
		};
	}
}

#endif

