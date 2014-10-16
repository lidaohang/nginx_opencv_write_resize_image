#include "convert_util.h"
using namespace dis::common;

ConvertUtil::ConvertUtil(void)
{
}


ConvertUtil::~ConvertUtil(void)
{
}
//int转string
string ConvertUtil::IntToString(int i){
	string c;
	ostringstream oss;
	oss<<i;
	c=oss.str();
	return c;
}

//string转int
int ConvertUtil::stringToInt(const string & str){

    int n=atoi(str.c_str()); 
	return n;

}
//字符串转大写
void ConvertUtil::ToUpperString(string & str)
{
    transform(str.begin(), str.end(), str.begin(), (int (*)(int))toupper);
}
//字符串转小写
void ConvertUtil::ToLowerString(string & str)
{
    transform(str.begin(), str.end(), str.begin(), (int (*)(int))tolower);
}

//static int php_htoi(char *s)
//{
//	int value;
//	int c;
//
//	c = ((unsigned char *)s)[0];
//	if (isupper(c))
//		c = tolower(c);
//	value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;
//
//	c = ((unsigned char *)s)[1];
//	if (isupper(c))
//		c = tolower(c);
//	value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;
//
//	return (value);
//}
//url解码
//string ConvertUtil::urldecode(string &str_source)
//{
//	char const *in_str = str_source.c_str();
//	int in_str_len = strlen(in_str);
//	int out_str_len = 0;
//	string out_str;
//	char *str;
//
//	str = _strdup(in_str);
//	char *dest = str;
//	char *data = str;
//
//	while (in_str_len--) {
//		if (*data == '+') {
//			*dest = ' ';
//		}
//		else if (*data == '%' && in_str_len >= 2 && isxdigit((int) *(data + 1)) 
//			&& isxdigit((int) *(data + 2))) {
//				*dest = (char) php_htoi(data + 1);
//				data += 2;
//				in_str_len -= 2;
//		} else {
//			*dest = *data;
//		}
//		data++;
//		dest++;
//	}
//	*dest = '\0';
//	out_str_len =  dest - str;
//	out_str = str;
//	free(str);
//
//	//最后的替换
//	const char * search_item = "\\";
//	const char * replace_item = "/";
//	string searchItem(search_item);
//	string replaceItem(replace_item);
//	string::size_type pos = 0;
//	while ( (pos = out_str.find(searchItem, pos)) != string::npos ) {
//		out_str.replace(pos, searchItem.size(), replaceItem);
//		pos++;
//	}
//    return out_str;
//}

//另一种方法

char dec2hexChar(short int n) {
 if ( 0 <= n && n <= 9 ) {
  return char( short('0') + n );
 } else if ( 10 <= n && n <= 15 ) {
  return char( short('A') + n - 10 );
 } else {
  return char(0);
 }
}

short int hexChar2dec(char c) {
 if ( '0'<=c && c<='9' ) {
  return short(c-'0');
 } else if ( 'a'<=c && c<='f' ) {
  return ( short(c-'a') + 10 );
 } else if ( 'A'<=c && c<='F' ) {
  return ( short(c-'A') + 10 );
 } else {
  return -1;
 }
}

std::string ConvertUtil::deescapeURL(const std::string & url) {
 string result = "";
 for ( unsigned int i=0; i<url.size(); i++ ) {
  char c = url[i];
  if ( c != '%' ) {
   result += c;
  } else {
   char c1 = url[++i];
   char c0 = url[++i];
   int num = 0;
   num += hexChar2dec(c1) * 16 + hexChar2dec(c0);
   result += char(num);
  }
 }

	//最后的替换
	const char * search_item = "\\";
	const char * replace_item = "/";
	string searchItem(search_item);
	string replaceItem(replace_item);
	string::size_type pos = 0;
	while ( (pos = result.find(searchItem, pos)) != string::npos ) {
		result.replace(pos, searchItem.size(), replaceItem);
		pos++;
	}
	return result;
}

std::string ConvertUtil::getErrorInfoJoint(string & errorInfo,int code){
	string result=",info:";
	result.append(errorInfo);
	result.append(",code:");
	result.append(IntToString(code));
	return result;
}


void add2Vector(vector<string> & resultList, const string & source, size_t offset, size_t last_pos=-1)
{
	string item;
	if(last_pos >= 0)
	{
		size_t substring_length = 0;
		substring_length = last_pos - offset;
		item = source.substr(offset, substring_length);
	}
	else
	{
		item = source.substr(offset);
	}		
	if(item.length() > 0)
	{		
		resultList.push_back(item);
	}
}

/*
	使用分隔符拆分字符串
*/
void ConvertUtil::splitStringByDelimiter(vector<string> & resultList, const string & source, const char & delimiter)
{
	if(source.length() == 0)
	{
		return;
	}
	string::size_type offset = 0;	//偏移量
	string::size_type last_pos = -1;	//最近一次匹配到分隔符的位置
	last_pos = source.find(delimiter, offset);
	while(last_pos != string::npos)
	{
		add2Vector(resultList, source, offset, last_pos);
		offset = last_pos + 1;
		//以后每次都设置
		last_pos = source.find(delimiter, offset);
	}
	add2Vector(resultList, source, offset);
}

//ImageType getType(const u_char* header)
//{
//	unsigned char jpeg_type[3] = {0xff, 0xd8,'/0'};
//	unsigned char bmp_type[3] = {0x42, 0x4D,'/0'};
//	unsigned char gif_type[8] = {0x47, 0x49, 0x46, 0x38, 0x39, 0x37, 0x61, '/0'};
//	unsigned char png_type[9] = {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A,'/0'};
//	switch(header[0])
//	{
//	case 0xff:
//		if(header[1] == jpeg_type[1])
//			return JPEG;
//	case 0x42:
//		if(header[1] == bmp_type[1])
//			return BMP;
//	case 0x89:
//		if(header[1]==png_type[1] && header[2]==png_type[2] && header[3]==png_type[3])
//			//&& header[4]==png_type[4] && header[5]==png_type[5] && header[6]==png_type[6] && header[7]==png_type[7])
//			return PNG;
//	case 0x47:
//		if(header[1]==gif_type[1] && header[2]==gif_type[2] && header[3]==gif_type[3] && (header[4]==gif_type[4] || header[4] == gif_type[5])
//			&& header[5] == gif_type[6])
//			return GIF;
//	default:
//		return Nothing;
//	}
//}

void ConvertUtil::statImage(const char* fileName, img_stat_t* imgStat)
{
	struct stat buf;	
	if (stat(fileName,&buf) || buf.st_ino < 0) {
		imgStat->exist = false;
		imgStat->size = 0;
		imgStat->type = Nothing;
		return;
	}
	imgStat->exist = true;
	imgStat->size = buf.st_size;	
	
	//u_char header[9];

	//ifstream file(fileName);
	//for (int i=0;i<8;++i) 
 //   {  
 //       file>>header[i];  
 //   }
	//header[8] = '/0';
	//imgStat->type = getType(&header[0]);
}

void ConvertUtil::statImage(image_data_t *data, img_stat_t* imgStat)
{
	imgStat->exist = true;
	imgStat->size = data->len;
	
	u_char header[9];	
	for (int i=0;i<8;++i) 
    {  
		header[i] = data->data[i];        
    }
	//header[8] = '/0';
	//imgStat->type = getType(&header[0]);
}

//long ConvertUtil::getRandom(long start, long end)
//{
//    return start+(end-start)*rand()/(RAND_MAX + 1);
//}

long ConvertUtil::getCurrentTime()  
{  
   /*struct timeval tv;  
   gettimeofday(&tv,NULL);  
   return tv.tv_sec * 1000 + tv.tv_usec / 1000; */ 
	return 100;
}
void ConvertUtil::fetch_file_data(string & fullpath,image_data_t * rt,const img_stat_t & imgStat)
{
	imgSize count=imgStat.size;

	char* datachar = new char[count];
	fstream infile;
	//读取文件内容
	infile.open(fullpath.c_str(),ios::in|ios::binary);
	infile.read(datachar,count);
	infile.close();
	//设置数据信息并返回
	rt->data = (u_char *)datachar;
	rt->len =  static_cast<off_t>(count);
}

 int   ConvertUtil::creatDir(   char   *sPathName)  
{  
  char   DirName[256];  
  strcpy(DirName,   sPathName);  
  int   i,len   =   strlen(DirName);  
  if(DirName[len-1]!='/')  
  strcat(DirName,   "/");  
   
  len   =   strlen(DirName);  
   
  for(i=1;   i<len;   i++)  
  {  
  if(DirName[i]=='/')  
  {  
  DirName[i]   =   0;  
  if(   access(DirName,   NULL)!=0   )  
  {  
      if(mkdir(DirName,   0755)==-1)  
      {   
                      perror("mkdir   error");   
                      return   -1;   
      }  
  }  
  DirName[i]   =   '/';  
  }  
  }  
   
  return   0;  
} 