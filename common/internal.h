#pragma once

#ifndef DIS_INTERNAL_H
#define DIS_INTERNAL_H

#include <string>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
//#include <sys/time.h>
#include  <iostream>
#include <fstream>
#include <sstream>
#include "dis_typedef_define.h"
#include <stdarg.h>
#include <sys/stat.h>




static  size_t NOT_FIND = 404;
static  size_t FORBIDDEN = 403;
static  size_t SERVER_INTERNAL_ERROR = 500;
static  size_t OK = 200;

static  std::string SUCCEED="1";
static  std::string FAILURE="-1";
static  off_t LEN=2;


#define TFS_NAME_REGEX "^T([\\w\\W]*){17}([\\w\\W]*)$"

enum ImageType{			
	PNG,
	JPEG,
	BMP,
	GIF,
	Nothing
};

typedef struct ImgStatType{
	bool exist;
	imgSize size;
	ImageType type;
	size_t sourceWidth;
	size_t sourceHeight;
	ImgStatType(bool _exist = false,size_t _sw=0, size_t _sh=0, imgSize _size=0, ImageType _type=Nothing):
	exist(_exist),
	size(_size),
	type(_type),
	sourceWidth(_sw), 
	sourceHeight(_sh){};
} img_stat_t;

typedef struct {
	int errorno;		//less zero = failed, 0 = success
	int detailno;
	bool match;		//true代表匹配了规则，false代表规则不匹配
} biz_checker_result_t;

#endif //DIS_INTERNAL_H
