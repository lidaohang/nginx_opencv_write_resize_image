#pragma once

#ifndef DIS_IMAGE_DATA_BLOCK_H
#define DIS_IMAGE_DATA_BLOCK_H

#include "dis_typedef_define.h"

typedef struct {
        off_t              len;
        u_char            *data;
		size_t             code;
		const char        *errorInfo;		
		u_char            *host;
		u_char            *uri;
		u_char            *complete_uri;
		u_char            *file_path;
		size_t             file_path_len;
		size_t             ret_source;
		void              *options;
		void              *rule;
		void              *operation;
} image_data_t;


//***********************************************
//	for c invoke c++, convert to c++ object
//***********************************************
typedef struct {
} empty_struct;

#endif /* DIS_IMAGE_DATA_BLOCK_H */
