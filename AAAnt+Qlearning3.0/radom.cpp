#include"main.h"
int random(int uper)//返回一个从0到最大随机数的任意整数
{
	return (rand() % uper);
};
double  random(int low, double uper)//生成某个区间内随机数的函数
{
	return (rand() / (double)RAND_MAX) * (uper - low) + low;
};