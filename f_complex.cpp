/*���������ģ*/
#include<math.h>
#include<Eigen/Core>
using namespace Eigen;
float f_complex_mod(MatrixXcf T)
{
	float a = T(0, 0)._Val[0];   //a�洢ʵ��
	float b = T(0, 0)._Val[1];   //b�洢�鲿
	return sqrt(a*a + b*b);       //����ģ(distance)
}