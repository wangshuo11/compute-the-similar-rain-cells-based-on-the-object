/*f_compare_two_cells������Ҫ���ڱȽ�����object(cell),������������Ʋ�Dֵ*/
#include<Eigen/Dense>   
#include<complex>         
#include<iostream>

 using namespace std;           
using namespace Eigen;

float f_res(MatrixXcf Zjk, MatrixXcf Zj, float Cavg_Zjk, float Cavg_Zj, float Cmin_Zjk, float Cmin_Zj, float Cmax_Zjk, float Cmax_Zj);//����Dֵ

float f_compare_two_cells(MatrixXcf Zj, float Cmin_Zj, float Cmax_Zj, float Cavg_Zj, int compare_j, float cells_intensities[][3], float cells_Z[][16])
{   /*��Ϊ�Ա�������Zjk������ʾ*/
	MatrixXcf Zjk(8, 1);
	for (int Zjk_i = 0; Zjk_i < 8; Zjk_i++) {
		Zjk(Zjk_i, 0)._Val[0] = cells_Z[compare_j][Zjk_i];
		Zjk(Zjk_i, 0)._Val[1] = cells_Z[compare_j][Zjk_i + 8];
	}

    /* ��Ϊ�Ա������Ľ���������*/
	float Cmin_Zjk = cells_intensities[compare_j][0];
	float Cmax_Zjk = cells_intensities[compare_j][1];
	float Cavg_Zjk = cells_intensities[compare_j][2];
	/*����cell�����ƶ�����*/
	float Fres = f_res(Zjk, Zj, Cavg_Zjk, Cavg_Zj, Cmin_Zjk, Cmin_Zj, Cmax_Zjk, Cmax_Zj); 
	return Fres;
}