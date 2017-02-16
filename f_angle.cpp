/*�������أ������ÿ����������ӦRes = ��x���꣬y����, ��Ӧ��ƫ��angle�������ĵ�ľ࣬�������ޣ�
���صĽ����һ������Res��ÿһ�зֱ��ǣ�x���꣬y����, ��Ӧ��ƫ��angle�������ĵ�ľ࣬�������ޣ�*/
#include<iostream>
#include<math.h>
#include<Eigen/Core>
#include<Eigen/Dense>
#include<complex>
using namespace std;
using namespace Eigen;

const float PI = 3.14159265358979323846;//Բ����PI

MatrixXf f_angle(MatrixXf boundary, float Cx, float Cy)
{
	float tx, ty, temp, value, dx, dy;    //��ʱ����
	int	k = boundary.rows();              //��������

										  //���ÿ��������������ĵ�ľ��룬�γɵ�ƫ�ǣ��Լ����ڵ�����(�ڼ����������)
	MatrixXf Res(k, 5);
	for (int i = 0; i < k; i++) {
		tx = boundary(i, 0);				//txȡ��iλ�����ص�x����
		ty = boundary(i, 1);				//tyȡ��iλ�����ص�y����
		temp = (ty - Cy) / (tx - Cx);	    //��������tan(y / x)
		value = atan(temp);                 //���������ֵvalue����ƫ��
		Res(i, 0) = tx;                     //����iѭ������Res()�������ݴ�
		Res(i, 1) = ty;                     //����iѭ������Res()�������ݴ�
		dx = tx - Cx;                       //���ص������cell���ĵ������ֵ��dx, dy��
		dy = ty - Cy;
		if (dx > 0) {                       //�������ĵ�Ϊԭ�㣬��������ϵ���ж����ޣ�����ϵ�Ľ�����opencvͼ������ϵһ��
			if (dy >= 0) {
				Res(i, 2) = value;                    //��Ӧ��ƫ����ֵ
				Res(i, 3) = sqrt(dx*dx + dy*dy);      //�����ĵ�ľ���
				Res(i, 4) = 1;                        //��������
			}
		}
		if (dx <= 0) {
			if (dy > 0) {
				Res(i, 2) = PI + value;					//��Ӧ��ƫ����ֵ
				Res(i, 3) = sqrt(dx*dx + dy*dy);        //�����ĵ�ľ���
				Res(i, 4) = 2;                          //��������
			}
		}
		if (dx < 0) {
			if (dy <= 0) {
				Res(i, 2) = value + PI;               //��Ӧ��ƫ����ֵ
				Res(i, 3) = sqrt(dx*dx + dy*dy);      //�����ĵ�ľ���
				Res(i, 4) = 3;                        //��������
			}
		}
		if (dx >= 0) {
			if (dy < 0) {
				Res(i, 2) = 2 * PI + value;             //��Ӧ��ƫ����ֵ
				Res(i, 3) = sqrt(dx*dx + dy*dy);        //�����ĵ�ľ���
				Res(i, 4) = 4;                          //��������
			}
		}
	}
	return Res;
}