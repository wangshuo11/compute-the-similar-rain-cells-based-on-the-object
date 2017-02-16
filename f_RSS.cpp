/*2007���Ĺ�ʽ��11��*/
#include<iostream>
#include<Eigen/Core>
#include<Eigen/Dense>
#include<complex>
#include<math.h>

using namespace std;
using namespace Eigen;

float f_RSS(MatrixXcf ZZj, MatrixXcf Zj)
{
	MatrixXcf t1, t2, t3;
	t1 = (ZZj - Zj).transpose();   //�ȼ���Zjk-Zj
	t2 = t1.conjugate();           //�������
	t3 = t2*(ZZj - Zj);            //���
	float RSS = t3(0, 0)._Val[0];  // ������
	return RSS;
}