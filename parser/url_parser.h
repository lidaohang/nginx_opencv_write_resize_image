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
				处理来自浏览器的图片请求
				host:								域名
				uri:								uri路径
				image_data_t:				处理后的图片数据
			*/
			void process(char * src_fullpath, char * des_fullpath, image_data_t * retval);
		};
	}

}