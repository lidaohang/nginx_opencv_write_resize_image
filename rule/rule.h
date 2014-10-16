#pragma once

#ifndef DIS_RULE_H_
#define DIS_RULE_H_

#include "../common/internal.h"


using namespace std;

namespace dis
{
	namespace rule
	{

			 struct Operation{
				size_t width;
				size_t height;
				size_t quality;
				size_t cut_width;
				size_t cut_height;
				char* dir;
				char* watermark;
				char* source_path;
				char* target_path;
				char*  data;
				Operation();
				//Operation(size_t width=0, size_t height=0, size_t quality=87):width(width), height(height), quality(quality){};
			};

	}
}
#endif 
