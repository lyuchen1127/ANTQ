#include"main.h"
int random(int uper)//����һ����0��������������������
{
	return (rand() % uper);
};
double  random(int low, double uper)//����ĳ��������������ĺ���
{
	return (rand() / (double)RAND_MAX) * (uper - low) + low;
};