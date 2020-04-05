#include <opencv2/opencv.hpp>
using namespace cv;

void getEencryptListFromImageSize(Size imagesize, vector<int> &list1, vector<int> &list2, double paDou1, double paDou2, double paK)
{
	int elementNum = imagesize.width*imagesize.height;
	double x1 = (paDou1 + paK) / 2;
	double x2 = (paDou2 + paK) / 2;
	//double x1 = (paDou1 ) / 2;
	//double x2 = (paDou2 ) / 2;
	double y1, y2, nowx1, nowx2;
	int tem, k1, k2;
	double lastx1 = x1;
	double lastx2 = x2;
	for (int i = 0; i < elementNum; i++)
	{
		nowx1 = 4*lastx1*(double(1)- lastx1);
		nowx2 = 4*lastx2*(double(1) - lastx2);
		y1 = (double(1) / 3.1415926)*asin(sqrt(nowx1));
		y2 = (double(1) / 3.1415926)*asin(sqrt(nowx2));
		tem = floor(y1*pow(10, 8));
		k1 = tem % 256;
		tem = floor(y2*pow(10, 6));
		k2 = tem % 256;
		list1.push_back(k1);
		list2.push_back(k2);
		lastx1 = nowx1;
		lastx2 = nowx2;
	}
}

Mat pictureDecrypt(Mat src, vector<int> list1, vector<int> list2)
{
	Mat dstImage = src.clone();
	int loop = 0;
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			int tem;
			if (loop % 2 == 0)
			{
				tem = list1[i*src.cols + j];
 
			}
			else
			{
				tem = list2[i*src.cols + j];
 
			}
			if (src.channels()==1)
			{
				int num = src.at<uchar>(i, j);
				int num1 = num^tem;
				dstImage.at<uchar>(i, j) = num1;
			}
			else if (src.channels() == 3)
			{
				int num0 = src.at<Vec3b>(i, j)[0];
				int num1 = src.at<Vec3b>(i, j)[1];
				int num2 = src.at<Vec3b>(i, j)[2];
				int res0 = num0^tem;
				int res1 = num1^tem;
				int res2 = num2^tem;
				dstImage.at<Vec3b>(i, j)[0] = res0;
				dstImage.at<Vec3b>(i, j)[1] = res1;
				dstImage.at<Vec3b>(i, j)[2] = res2;
			}
			loop = loop + 1;
			if (loop ==925444)
			{
				cout << "" << endl;
			}
		}
	}
	return dstImage;
}

