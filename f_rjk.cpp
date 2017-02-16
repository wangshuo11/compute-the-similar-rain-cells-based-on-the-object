/*2007���Ĺ�ʽ(8)�е�1����ʽ*/
#include<Eigen/Core>
#include<Eigen/Dense>

using namespace Eigen;

float f_complex_mod(MatrixXcf T);  //���㸴����ģ��

float f_rjk(MatrixXcf Zjkc, MatrixXcf Zjc)
{
	MatrixXcf t1, t2, t3, t4;          //�����м���㣬��Ϊ�м����
	float T_rjk;                       //����������������  
	t1 = Zjkc.transpose();             //Zjkc����ת��
	t2 = t1.conjugate();               //t1������
	t3 = t2*Zjc;                       //��������������ˣ�������Ǹ�������
	t4 = t2*Zjkc;                      //��������������ˣ�������Ǹ�������
	T_rjk = f_complex_mod(t3) / f_complex_mod(t4);        //f_complex_mod()����������һ��������ģ
	return T_rjk;
}