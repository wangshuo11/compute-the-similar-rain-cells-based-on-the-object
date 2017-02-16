/*2007���Ĺ�ʽ��7��*/
#include<iostream>
#include<Eigen/Core>
#include<Eigen/Dense>
#include<complex>

using namespace std;
using namespace Eigen;

MatrixXcf f_ZZj(MatrixXcf Bjk, float Rjk, float FFjk, MatrixXcf Zjk)
{
	complex<float> T_FFjk(0, FFjk);  //��FFjkת��Ϊ�����������ڹ�ʽ����
	MatrixXcf ZZj = Bjk + Rjk*exp(T_FFjk)*Zjk;  //���չ�ʽ����
	return ZZj;
}