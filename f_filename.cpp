#include<string.h>
#include<iostream>
using namespace std;

/* ��ȡ�ļ�·������*/
void f_filename(int dat_i, char filename[])
{
	char numtostr[20];
	_itoa(dat_i, numtostr, 10);
	char filename0[40] = "F:\\anal\\anal_";
	strcpy(filename, filename0);
	strcat(filename, numtostr);
	char filename1[10] = ".dat";
	strcat(filename, filename1);
}