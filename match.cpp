#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/utility.hpp"

#include <stdio.h>

using namespace cv;

int main()
{
	//Ptr<StereoBM> bm = StereoBM::create(16, 9);
	//bm->setROI1(roi1);
	//bm->setROI2(roi2);
	//bm->setPreFilterCap(31);
	////bm->setBlockSize(SADWindowSize > 0 ? SADWindowSize : 9);
	//bm->setBlockSize(15);
	//bm->setMinDisparity(0);//两个摄像头前向平行放置，故设为0
	////bm->setMinDisparity(16);
	////bm->setNumDisparities(numberOfDisparities);
	//bm->setNumDisparities(32);
	//bm->setTextureThreshold(10);
	//bm->setUniquenessRatio(15);
	////bm->setUniquenessRatio(10);
	//bm->setSpeckleWindowSize(100);
	//bm->setSpeckleRange(32);
	//bm->setDisp12MaxDiff(1);

	//Mat img1 = imread("tsukubaleft.jpg", 0);
	//Mat img2 = imread("tsukubaright.jpg", 0);
	//bm->compute(img1, img2, disp);


	IplImage* img1 = cvLoadImage("tsukubaleft.jpg", 0);
	IplImage* img2 = cvLoadImage("tsukubaright.jpg", 0);
	CvMat* disparity = cvCreateMat(img1->height, img1->width, CV_32FC1);//声明一个矩阵，大小与加载图像一致，为浮点型
	CvMat* norm_disparity = cvCreateMat(img2->height, img2->width, CV_8U);//声明一个矩阵，大小与加载图像一致，为无符号型

	CvStereoBMState *BMState = cvCreateStereoBMState();

	int SADWindowSize = 15;
	BMState->SADWindowSize = SADWindowSize > 0 ? SADWindowSize : 9;
	BMState->minDisparity = 0;
	BMState->numberOfDisparities = 32;
	BMState->textureThreshold = 10;
	BMState->uniquenessRatio = 15;
	BMState->speckleWindowSize = 100;
	BMState->speckleRange = 32;
	BMState->disp12MaxDiff = 1;
	cvFindStereoCorrespondenceBM(img1, img2, disparity, BMState);		//校正图像
	cvNormalize(disparity, norm_disparity, 0, 256, CV_MINMAX, NULL);	//图像归一化

	//图像显示
	cvShowImage("img", norm_disparity);
	cvWaitKey(0);

	//释放所有图像指针占内存与矩阵所占内存，关闭窗口
	cvDestroyAllWindows();
	cvReleaseImage(&img1);
	cvReleaseImage(&img2);
	cvReleaseMat(&disparity);
	cvReleaseMat(&norm_disparity);

	/*cvFindStereoCorrespondenceBM(img1, img2, left_disp_, BMState);
	cvNormalize(left_disp_, left_vdisp, 0, 256, CV_MINMAX);

	namedWindow("disp", 0);
	imshow("disp", disp);*/
	return 0;
}
