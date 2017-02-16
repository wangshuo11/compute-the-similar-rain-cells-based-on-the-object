#include<iostream>
#include<Eigen/Dense>
#include<fstream>
#include<string.h>
using namespace std;
using namespace Eigen;

const int scale = 4000;
const int filenum = 4381;
int date[filenum + 10][3];
float cells_Z[scale][16];
char cells_Id[scale][100];
float cells_intensities[scale][3];

/*f_hash_date()��ϣ���ļ�˳������ڵ�ӳ���f_hash_cells()�ó�ÿһ�������ı��Id����������������ʾ�Լ�����������ֵ*/
void f_hash_cells(int date[][3], char cells_Id[][100], float cells_Z[][16], float cells_intensities[][3], int &count_cells);
void f_hash_date(int date[][3]);
void f_savename(int pos, char savename[]);
float f_compare_two_cells(MatrixXcf Zj, float Cmin_Zj, float Cmax_Zj, float Cavg_Zj, int compare_j, float cells_intensities[][3], float cells_Z[][16]);

int main()
{
	f_hash_date(date);
	int count_cells = 0;//count_cells����ͳ���������ж��ٸ�����
	f_hash_cells(date, cells_Id, cells_Z, cells_intensities, count_cells);

	/*�ҳ���ʷ����ÿ���������Ƶ������ģ����ҽ���ű�����·��savename��*/
	for (int i = count_cells - 1; i >0; i--) {
		
		/*����������������������*/
		MatrixXcf Zj(8, 1);
	
		for (int Zj_i = 0; Zj_i < 8; Zj_i++) {
			Zj(Zj_i, 0)._Val[0] = cells_Z[i][Zj_i];
			Zj(Zj_i, 0)._Val[1] = cells_Z[i][Zj_i + 8];
		}
		float Cmin_Zj = cells_intensities[i][0];
		float Cmax_Zj = cells_intensities[i][1];
		float Cavg_Zj = cells_intensities[i][2];

		char savename[100];
		f_savename(i, savename);
		ofstream out(savename);
		out << cells_Id[i] << endl;
		/*����������ʷ�ϵ��������Ҿ���һ�����Ƶ�����*/
		for (int compare_j = i - 1; compare_j >= 0; compare_j--) {
			float res_compare = f_compare_two_cells(Zj, Cmin_Zj, Cmax_Zj, Cavg_Zj, compare_j, cells_intensities, cells_Z);
			if (res_compare< 15) {
				out << cells_Id[compare_j] << endl;
			}
		}
	}
	
	return 0;
}