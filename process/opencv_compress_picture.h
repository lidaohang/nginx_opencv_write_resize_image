#pragma once

#ifndef DIS_DATA_OPENCV_COMPRESS_PICTURE_H_
#define DIS_DATA_OPENCV_COMPRESS_PICTURE_H_

#include "../common/internal.h"
#include "../common/image_data_block.h"
#include "../rule/rule.h"



using namespace dis::rule;

namespace dis{
	namespace process{
		//opencv图片处理类
		class OpenCvCompressPicture 
		{
		public:
			OpenCvCompressPicture();
			 ~OpenCvCompressPicture();
			 /*通过传入data处理数据
		     operation：数据信息封装类 包括压缩、水印信息等
		     retVal：数据源，包括传入数据源及处理后数据信息
			*/
			void resizeImage(Operation  *operation, image_data_t * retVal);
			/*通过传入文件路径处理数据，暂未使用
			*/
			
		};
	}
}
#endif	//DIS_DATA_OPENCV_COMPRESS_PICTURE_H_

