/*2007���Ĺ�ʽ(8)�е�3����ʽ*/
#include<Eigen/Core>
#include<Eigen/Dense>
#include<complex>
#include<iostream>

using namespace Eigen;
using namespace std;

MatrixXcf f_Bjk(MatrixXcf Zjk_avg, MatrixXcf Zj_avg, float Rjk, float FFjk)
{
	complex<float> T_FFjk(0, FFjk);      //��FFjkת��Ϊ�����������ڹ�ʽ����
	MatrixXcf Bjk = Zj_avg - Rjk*exp(T_FFjk)*Zjk_avg;   //���չ�ʽ����
	return Bjk;
}