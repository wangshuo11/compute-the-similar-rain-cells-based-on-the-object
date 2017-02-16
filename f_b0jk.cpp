/*2007���Ĺ�ʽ(8)�е�4����ʽ*/
#include<iostream>
#include<Eigen/Core>
#include<Eigen/Dense>
#include<complex>

using namespace std;
using namespace Eigen;

complex<float> f_b0jk(MatrixXcf Zjk, MatrixXcf Zj, float Rjk, float FFjk)
{
	complex<float> T_FFjk(0, FFjk);      //��FFjkת��Ϊ�����������ڹ�ʽ����
	complex<float> T_b0jk = Zjk.sum() - Rjk*exp(T_FFjk)*Zj.sum();     //�ȼ����м���
	complex<float> b0jk(T_b0jk.real() / 7.0, T_b0jk.imag() / 7.0);     //ʵ�����鲿�ֱ����A-1(�˴�A��Ĭ��Ϊ8)
	return b0jk;
}
