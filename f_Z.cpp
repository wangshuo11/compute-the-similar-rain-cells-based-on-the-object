/*������(Cx, Cy)Ϊƫ�����ĵ㣬�������ƫ�ǣ�2*pi(L - 1)(/ A - 1)��, L = 0, 1...A - 1)ֵ���߽�����edge
���ཻ�����ص�����ꡣ�������ص��ƫ��ֵ����ĳ��������������ĵ�ƫ��alpha������ƫ��angle���С��pi / 16ʱ��
�ɿ���ʹ�ø�λ�ü�¼Ϊ��Ӧ��ƫ��λ�ã����ж��λ������ʱ��ʹ�������С����Ϊ���λ�á�
�������ķ�Χ���Ҳ������ʵĵ�������ƫ��anglgʱ��߽�����Ľ���ʱ��ȡ�������ص��е����ĵ���Զ��R��
��¼��λ��Ϊx = Cx + R*sin(angle), y = Cy + R*cos(angle)*/
#include<math.h>
#include<iostream>
#include<Eigen/Core>
#include<Eigen/Dense>
#include<complex>

using namespace std;
using namespace Eigen;
const float PI = 3.14159265358979323846;//Բ����PI

MatrixXcf f_Z(MatrixXf Res, float Cx, float Cy) {
	MatrixXcf Z(8, 1);
	int k, pos = 0;
	float X_Rmax, Y_Rmax, flag, angle, t_min, t_abs, t_cha, tx, ty, t_r, Rmax = Res(0, 3);
	flag = PI / 16;              // ���������(flag)
								 //Ѱ�Ҿ������ĵ���Զ�ĵ�
	k = Res.rows();
	for (int i = 1; i < k; i++) {
		if (Rmax< Res(i, 3)) {    //������Զ����
			Rmax = Res(i, 3);
			pos = i;
		}
	}
	X_Rmax = Res(pos, 0);    //��Զ����������x,y
	Y_Rmax = Res(pos, 1);
	//�������ƫ�Ǻ;������ʺϵĵ�
	for (int i = 0; i < 8; i++) {
		angle = i * 2 * PI / 8.0;       //���²���ƫ��
		t_min = 5 * PI;
		for (int j = 0; j < k; j++) {
			t_cha = abs(Res(j, 2) - angle);
			t_abs = abs(t_min - angle);
			if (t_cha<t_abs) {     //���������
				t_r = Res(j, 3);
				t_min = Res(j, 2);
				tx = Res(j, 0);
				ty = Res(j, 1);
			}
		}

		if (abs(t_min - angle)>flag) {      //�ж���������ڲ���ƫ����Χ�ڣ���������ʹ��Rmax
			t_r = Rmax;
			t_min = angle;
			tx = cos(angle) + Cx;
			ty = sin(angle) + Cy;
		}
		Z(i, 0)._Val[0] = tx;   //Z�а���˳���ű�ѡ�е�(x,y)����
		Z(i, 0)._Val[1] = ty;
	}
	return Z;
}