/*2007���Ĺ�ʽ(8)�е�2����ʽ*/
#include<Eigen/Core>
#include<Eigen/Dense>
#include<complex>
#include<math.h>

using namespace Eigen;
using namespace std;
void f_filename(int dat_i, char filename[]);
float f_FFjk(MatrixXcf Zjkc, MatrixXcf Zjc)
{
	MatrixXcf t1, t2, t3;
	t1 = Zjkc.transpose();         //ת��
	t2 = t1.conjugate();           //����
	t3 = t2*Zjc;                   //���
	complex<float> cm(t3(0, 0)._Val[0], t3(0, 0)._Val[1]);  //��MatrixXcf���� ת��Ϊ complex ����
	return arg(cm);                                     //�������
}