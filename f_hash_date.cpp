/*f_hash_date��Ҫ�����ļ���˳��i������������Ӧ�����ڣ��������ڷ���date[][]�У����ڲ���*/
#include<iostream>
using namespace std;
const int filenum = 4381;
int f_isyear(int year);            //�ж��Ƿ�������
void f_hash_date(int date[][3])
{
	int month[12][2] = { 31, 31,          //month[][0]��ʾƽ���·ݵ�������month[][1]��ʾ�����·ݵ�����
		28, 29,
		31, 31,
		30, 30,
		31, 31,
		30, 30,
		31, 31,
		31, 31,
		30, 30,
		31, 31,
		30, 30,
		31, 31 };
	int day = 1, mon = 1, year = 2002;     //��ʼ��������Ϊ�ļ���ʼ����
										   /*ͨ��hash,���ν��ļ�˳����ֵi,����Ӧ�����ڷ���date[i][]��*/
	for (int i = 0; i <filenum; i++) {
		day = day + 1;
		if (day > month[mon - 1][f_isyear(year)]) {      //���������·�������day=1,mon++
			day = 1;
			mon = mon + 1;
		}
		if (mon > 12) {              //�·ݴ���12���£�mon=1,year++
			mon = 1;
			year = year + 1;
		}
		/*���浽date[][]��*/
		date[i][0] = year;
		date[i][1] = mon;
		date[i][2] = day;
	}
}
