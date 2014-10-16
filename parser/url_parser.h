#pragma once

#include "../common/internal.h"
#include "../common/image_data_block.h"

using  namespace  std;

namespace dis
{
	namespace parser{	
		class UrlParser
		{
		public:
		UrlParser(void);
		~UrlParser(void);

		/*
				���������������ͼƬ����
				host:								����
				uri:								uri·��
				image_data_t:				������ͼƬ����
			*/
			void process(char * src_fullpath, char * des_fullpath, image_data_t * retval);
		};
	}

}