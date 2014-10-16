#pragma once

#ifndef DIS_DATA_OPENCV_COMPRESS_PICTURE_H_
#define DIS_DATA_OPENCV_COMPRESS_PICTURE_H_

#include "../common/internal.h"
#include "../common/image_data_block.h"
#include "../rule/rule.h"



using namespace dis::rule;

namespace dis{
	namespace process{
		//opencvͼƬ������
		class OpenCvCompressPicture 
		{
		public:
			OpenCvCompressPicture();
			 ~OpenCvCompressPicture();
			 /*ͨ������data��������
		     operation��������Ϣ��װ�� ����ѹ����ˮӡ��Ϣ��
		     retVal������Դ��������������Դ�������������Ϣ
			*/
			void resizeImage(Operation  *operation, image_data_t * retVal);
			/*ͨ�������ļ�·���������ݣ���δʹ��
			*/
			
		};
	}
}
#endif	//DIS_DATA_OPENCV_COMPRESS_PICTURE_H_

