#include "opencv_compress_picture.h"
#include <cv.h>
#include <highgui.h>
#include "../common/log.h"
#include "../common/convert_util.h"


using namespace dis::rule;
using namespace dis::process;
using namespace dis::common;

using namespace cv;


OpenCvCompressPicture::OpenCvCompressPicture(void)
{
}


OpenCvCompressPicture::~OpenCvCompressPicture(void)
{

}

//log
static Logs logger=Logs::instance();



void  scanSize(Operation  *operation,Mat img)
{
	//��ȡԭͼ�Ŀ�͸�
	size_t src_width=img.size().width;
	size_t src_height=img.size().height;
	//����ԭͼ��Ҫѹ���ı���
	float scale_width=src_width/operation->width;
	float scale_height=src_height/operation->height;
	//�����ı���С���ڵ��ڸߵı��������տ���ѹ�� ����ֵС������
	if(scale_width<=scale_height)
	{
		logger.write_debug("opencv  image primary  is  width ");
		//Ŀ���=ԭ��/(ԭ��/Ŀ���)
		float tmp_width=(float)src_width/(float)operation->width;
		size_t des_height=src_height/tmp_width;
		if (operation->height != des_height)
		{//���Ŀ��ߺ�����Ҫѹ���ĸߣ���ͳһ�͵���ѹ������ü�
			operation->cut_height=operation->height;
			operation->height=des_height;
		}
	}
	//���ո���ѹ�� ����ֵС������
	else
	{
		logger.write_debug("opencv  image primary  is  height ");
		//Ŀ���=ԭ��/(ԭ��/Ŀ���)
		float tmp_height=(float)src_height/(float)operation->height;
		size_t des_width=src_width/tmp_height;
		if (operation->width != des_width)
		{//���Ŀ��������Ҫѹ���Ŀ���ͳһ�͵���ѹ������ü�
			operation->cut_width=operation->width;
			operation->width=des_width;
		}
	}
}

void saveImage(Operation  *operation, image_data_t * retVal,IplImage * dst)
{
	logger.write_debug("opencv  image path dir mkdir");
	ConvertUtil::Instance()->creatDir(operation->dir);

	logger.write_debug(operation->target_path);
	int params[3] = {0};
    params[0] = CV_IMWRITE_JPEG_QUALITY;
    params[1] = operation->quality;//opencv Ĭ�ϵ�ѹ������95

	logger.write_debug("opencv  image cvsave begin");
	int num=cvSaveImage(operation->target_path , dst ,params);
	
	if(num!=1)
	{
		retVal->code=SERVER_INTERNAL_ERROR;
		retVal->data=NULL;
		retVal->len=strlen(FAILURE.c_str());
		logger.write_error("opencv image cvsave error");
		return;
	}
}

void OpenCvCompressPicture::resizeImage(Operation  *operation, image_data_t * retVal)
{
	logger.write_debug("opencv resize begin");
	if(operation->source_path == NULL)
	{
		retVal->code=NOT_FIND;
		retVal->data=(u_char *)FAILURE.c_str();
		retVal->len=LEN;
		logger.write_error("operation->source_path is null");
		return;
	}
	logger.write_debug("opencv load image ");
	logger.write_debug(operation->source_path);
	
	Mat img=imread(operation->source_path);
	if (img.data == NULL)
	{
		retVal->code=SERVER_INTERNAL_ERROR;
		retVal->data=(u_char *)FAILURE.c_str();
		retVal->len=LEN;
		logger.write_error("Mat source is null");
		return;
	}
	scanSize(operation,img);

	IplImage src_img=img;
	IplImage* source=&src_img;


	logger.write_debug("opencv  image cvresize");
	IplImage * dst = NULL;
	CvSize dst_cvsize;
	dst_cvsize.width = operation->width;
	dst_cvsize.height = operation->height;
	dst = cvCreateImage(dst_cvsize, source->depth, source->nChannels);    //����Ŀ��ͼ��	
	cvResize(source, dst, CV_INTER_AREA); 
	
	if(dst == NULL)
	{
		retVal->code=SERVER_INTERNAL_ERROR;
		retVal->data=(u_char *)FAILURE.c_str();
		retVal->len=LEN;
		logger.write_error("IplImage dst  is null");
		return;
	}
	
	size_t cut_width=0;
	size_t cut_height=0;
	if(operation->cut_height>0)
	{
		cut_width=operation->width;
		cut_height=operation->cut_height;
	}
	else if(operation->cut_width>0)
	{
		cut_height=operation->height;
		cut_width=operation->cut_width;
	}
	
	if(cut_width>0 && cut_height>0){
		
		logger.write_debug("opencv  image cut");
		cvSetImageROI(dst,cvRect(0,0,cut_width,cut_height));  
		IplImage* dst_cut = cvCreateImage(cvSize(cut_width,cut_height),dst->depth,dst->nChannels);  
		cvCopy(dst,dst_cut,0);  
		cvResetImageROI(dst);
		saveImage(operation,retVal,dst_cut);
		cvReleaseImage(&dst_cut);
	}
	else
	{
		logger.write_debug("opencv  image not cut");
		saveImage(operation,retVal,dst);
		cvReleaseImage(&dst);
	}
	
	retVal->code=OK;
	retVal->data = (u_char *)malloc((SUCCEED.length()+1)*sizeof(u_char));
	memcpy(retVal->data,SUCCEED.c_str(),SUCCEED.length());
	retVal->len=strlen(SUCCEED.c_str());
	
	//cvReleaseImage(&source);
	
	logger.write_debug("opencv  image cvsave end");
}