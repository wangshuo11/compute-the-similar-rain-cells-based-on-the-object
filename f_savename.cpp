#include<string.h>
#include<iostream>
using namespace std;

/*��ȡ�ļ�����·��*/

void f_savename(int pos, char savename[])
{
	char numtostr[20];
	_itoa(pos, numtostr, 10);

	char savename0[40] = "F:\\data_by_object\\similar_";
	strcpy(savename, savename0);
	strcat(savename, numtostr);
	char savename1[10] = ".txt";
	strcat(savename, savename1);
}