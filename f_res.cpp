/*2007���Ĺ�ʽ(13)
����cell�ľ����ʾ����� SEmin��Min intensity SE����SEmax��Max intensity SE����SEavg��Avg intensity SE����
Ed��Dilation SE����SEr��Rotation SE����SEt��Translation SE����RSE��Residual SE����D��Cell penalty��*/
#include<iostream>
#include<Eigen/Core>
#include<Eigen/Dense>
#include<complex>

using namespace std;
using namespace Eigen;

/*���� f_rjk(),f_FFjk(),f_Bjk(),f_B0jk(),f_ZZj(),f_RSS()�Ⱥ���,
�ֱ����rjk,FFjk,Bjk,B0jk,ZZj,RSS��*/
float f_rjk(MatrixXcf Zjkc, MatrixXcf Zjc);
float f_FFjk(MatrixXcf Zjkc, MatrixXcf Zjc);
MatrixXcf f_Bjk(MatrixXcf Zjk_avg, MatrixXcf Zj_avg, float Rjk, float FFjk);
complex<float> f_b0jk(MatrixXcf Zjk, MatrixXcf Zj, float Rjk, float  FFjk);
MatrixXcf f_ZZj(MatrixXcf Bjk, float Rjk, float FFjk, MatrixXcf Zjk);
float f_RSS(MatrixXcf ZZj, MatrixXcf Zj);

float f_res(MatrixXcf Zjk, MatrixXcf Zj, float Cavg_Zjk, float Cavg_Zj, float  Cmin_Zjk, float Cmin_Zj, float Cmax_Zjk, float Cmax_Zj)
{
	int len_Zjk_row = Zjk.rows();             //����Zjk����ĳ���
	int len_Zj_row = Zj.rows();               //����Zj�ľ��󳤶�
	complex<float> T_Zjk = Zjk.mean();        //���Zjk��ֵ�����ں������
	complex<float> T_Zj = Zj.mean();           //���Zj��ֵ�����ں������

											   //ѭ����ʼ������Zjk_avg��Zj_avg��ֵΪ1+0*i��������ʽ��
	MatrixXcf Zjk_avg(len_Zjk_row, 1), Zj_avg(len_Zjk_row, 1);
	for (int i = 0; i < len_Zjk_row; i++) {
		Zjk_avg(i, 0)._Val[0] = 1;
		Zjk_avg(i, 0)._Val[1] = 0;
		Zj_avg(i, 0)._Val[0] = 1;
		Zj_avg(i, 0)._Val[1] = 0;
	}

	//2007�깫ʽ��9��
	Zjk_avg = Zjk_avg*(len_Zjk_row) / (len_Zjk_row - 1)*T_Zjk;
	Zj_avg = Zj_avg*(len_Zj_row) / (len_Zj_row - 1)*T_Zj;
	//����Zjkc��Zjc��Ӧ���Ĺ�ʽ��9���ͣ�10����һ��
	MatrixXcf Zjkc = Zjk - Zjk_avg;
	MatrixXcf Zjc = Zj - Zj_avg;

	//����Rjk��FFjk��Bjk��B0jk(2007�����Ĺ�ʽ(8))��ZZj(2007�����Ĺ�ʽ(7))
	float Rjk = f_rjk(Zjkc, Zjc);
	float FFjk = f_FFjk(Zjkc, Zjc);
	MatrixXcf Bjk = f_Bjk(Zjk_avg, Zj_avg, Rjk, FFjk);
	complex<float> B0jk = f_b0jk(Zjk, Zj, Rjk, FFjk);
	MatrixXcf ZZj = f_ZZj(Bjk, Rjk, FFjk, Zjk);

	//����SEd��SEr��SEt��RSE  ��Ӧ�����й�ʽ��13��
	float SEmin = (Cmin_Zj - Cmin_Zjk)*(Cmin_Zj - Cmin_Zjk);
	float SEmax = (Cmax_Zj - Cmax_Zjk)*(Cmax_Zj - Cmax_Zjk);
	float SEavg = (Cavg_Zj - Cavg_Zjk)*(Cavg_Zj - Cavg_Zjk);

	//����SEmin��SEmax��SEavg��SEd��SEr��SEt��RSE  ��Ӧ�����й�ʽ��14��
	float SEd = Rjk*Rjk;
	float SEr = FFjk*FFjk;
	float SEt = abs(B0jk*B0jk);

	//RSS����RSE��Ӧ��2007�����й�ʽ��10��
	float RSE = f_RSS(ZZj, Zj);

	//����D, Ȩ�ذ��չ�ʽ������(w1, w2, w3, w4, w5, w6, w7)  ��Ӧ2010�����й�ʽ��3��
	float w1 = 0.2, w2 = 0.2, w3 = 0.2, w4 = 0.2, w5 = 0.1, w6 = 0.05, w7 = 0.05;
	float D = w1*sqrt(RSE) + w2*(SEavg)+w3*(SEmin)+w4*(SEmax)+w5 * 100 * abs(1 - SEd) + w6 * 100 * SEr + w7*sqrt(SEt);

	//�����ȫ������Res()
	/*MatrixXf Res(1, 8);
	Res << SEmin, SEmax, SEavg, SEd, SEr, SEt, RSE, D;
	return Res;*/
	return D;
}