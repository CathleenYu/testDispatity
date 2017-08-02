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
	//bm->setMinDisparity(0);//��������ͷǰ��ƽ�з��ã�����Ϊ0
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
	CvMat* disparity = cvCreateMat(img1->height, img1->width, CV_32FC1);//����һ�����󣬴�С�����ͼ��һ�£�Ϊ������
	CvMat* norm_disparity = cvCreateMat(img2->height, img2->width, CV_8U);//����һ�����󣬴�С�����ͼ��һ�£�Ϊ�޷�����

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
	cvFindStereoCorrespondenceBM(img1, img2, disparity, BMState);		//У��ͼ��
	cvNormalize(disparity, norm_disparity, 0, 256, CV_MINMAX, NULL);	//ͼ���һ��

	//ͼ����ʾ
	cvShowImage("img", norm_disparity);
	cvWaitKey(0);

	//�ͷ�����ͼ��ָ��ռ�ڴ��������ռ�ڴ棬�رմ���
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
