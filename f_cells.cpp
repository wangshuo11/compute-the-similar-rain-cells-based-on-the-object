/* f_cells()��Ҫ�����ÿ������cell��(x + i*sin(angle)*y...)��������ʾ����Z,
�ڼ����ÿ��cell��Z_intensity(Cx, Cy, Cmin, Cmax, Cavg)��Cell������(Cx, Cy)����ˮǿ����Сֵ���ֵ�Լ���ֵ��Cmin, Cmax, Cavg��*/
#include<Eigen/Dense>   
#include<complex>         
#include<iostream>
#include<math.h>
#include <opencv2/opencv.hpp>     

using namespace std;           //�����ռ�
using namespace Eigen;
using namespace cv;

const int len_row = 128;     //���ݶ������ļ�����ͼ��Ŀ�͸�
const int len_col = 61;
const int file_size = 7808;
const int threshold_value_rain = 25;   //���ý��������˵���ֵ
const int threshold_value_contours = 6;  //�����������˵���ֵ

MatrixXf f_intensities(char *filename);
MatrixXf f_angle(MatrixXf boundary, float Cx, float Cy);
MatrixXcf f_Z(MatrixXf Res, float Cx, float Cy);

MatrixXcf f_cells(char *filename)
{
	FILE *fp = fopen(filename, "rb");  //�Զ�������ʽ���ļ�
	MatrixXcf A(1, 1);
	A << (-1, -1);
	if (fp == NULL) {
		cout << "No such file" << endl;
		exit(-1);
	}
	/*���ĸ��ֽ�Ϊ��λ�����ζ�ȡfp��ָ�����ֵ������ͨ����ֵthreshold_value����*/
	float temp;
	Mat I0(len_row, len_col, CV_32F), I1(len_row, len_col, CV_32F), I2;
	for (int i = 0; i < file_size; i++) {
		fread(&temp, 4, 1, fp);
		if (temp > threshold_value_rain) {
			I0.at<float>(i / len_col, i%len_col) = temp;
			I1.at<float>(i / len_col, i%len_col) = 255;
		}
		else {
			I0.at<float>(i / len_col, i%len_col) = 0;
			I1.at<float>(i / len_col, i%len_col) = 0;
		}
		fseek(fp, 4L, 1);            //�ļ�ָ����ƣ�������ȡ����
	}
	fclose(fp);//�ر��ļ�
			 
	/*��ȡ��������������������ȥ������С����������Բ���ʱ�������������������*/
	I1.convertTo(I2, CV_8U, 1, 0);
	vector<vector<Point>> contours;
	vector<vector<Point>> contours2;
	vector<Vec4i> hierarchy;
	Point temp_point;
	findContours(I2, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i<contours.size(); i++) {
		if (contours[i].size()>threshold_value_contours) {          //����ȥ������С������
			Mat pointsf;
			Mat(contours[i]).convertTo(pointsf, CV_32F);
			RotatedRect box = fitEllipse(pointsf);
			if (max(box.size.height, box.size.width) > 15 * min(box.size.height, box.size.width))       //��������Բ��Ͻ�Ϊ����������������
				continue;
			vector<Point> temp_vector;
			for (int j = 0; j < contours[i].size(); j++) {
				temp_point.x = contours[i][j].x;
				temp_point.y = contours[i][j].y;
				temp_vector.push_back(temp_point);
			}
			contours2.push_back(temp_vector);   //���˺������
		}
	}
	MatrixXf intensities = f_intensities(filename).transpose();  //ת��
	MatrixXf Z_intensities = intensities;
	int k = intensities.cols();                //ÿһ��������������ͬһ�У�����������������Ŀ
	MatrixXcf Z(8, k);
	/*���μ���ÿ��������������ʾZ;*/
	for (int i = 0; i < k; i++) {
		float Cx = intensities(0, i);        //������������
		float Cy = intensities(1, i);
	    /*������ȡÿ������������������Z������ʾ*/
		MatrixXf B(contours2[i].size(), 2);
		for (int j = 0; j < contours2[i].size(); j++) {
			B(j, 0) = contours2[i][j].x;
			B(j, 1) = contours2[i][j].y;
		}
		
		MatrixXf Res = f_angle(B, Cx, Cy);
		MatrixXcf temp = f_Z(Res, Cx, Cy);
		for (int j = 0; j < 8; j++) {
			Z(j, i)._Val[0] = temp(j, 0)._Val[0];
			Z(j, i)._Val[1] = temp(j, 0)._Val[1];
		}
	}
	if (contours2.size() > 0)
		return Z;
	else
		return A;
}