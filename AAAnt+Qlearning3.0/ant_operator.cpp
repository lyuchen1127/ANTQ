#include"main.h"
int random(int uper);//返回一个从0到最大随机数的任意整数

double  random(int low, double uper);//生成某个区间内随机数的函数
void Ant_Initial(solution_Ant *Ant_temp)//蚂蚁的构造函数
{
	Ant_temp->tour_length  = 0;
	
	Ant_temp->tour_citycount = 0;//起初所旅行过的城市数量为0
	for (int i = 0; i < CityCount; i++)
	{
		Ant_temp->can_visit[i] = true;//每个城市都可以访问
		Ant_temp-> select_probability[i] = 0;//选择各个城市的概率为0
	}
}

void Ant_Clear(solution_Ant* Ant_temp)
{
	Ant_temp->tour_length = 0;
	for (int i = 0; i < CityCount; i++)
	{
		Ant_temp->select_probability[i] = 0;
		Ant_temp->can_visit[i] = true;
	}
	Ant_temp->tour_citycount = 0;

}

void Ant_Addcity(solution_Ant* Ant_temp,int city)
{
	//add city to tabu;
	Ant_temp->tour[Ant_temp->tour_citycount] = city;
	Ant_temp->tour_citycount++;
	Ant_temp->can_visit[city] = false;
}

void Ant_GetFirstCity(solution_Ant* Ant_temp)
{
	srand((unsigned)time(NULL) + rand());
	Ant_Addcity(Ant_temp,random(CityCount));
}

void Ant_Next_City(solution_Ant* Ant_temp,double τ[CityCount][CityCount],double Deltτ[CityCount][CityCount], double alldisarray[CityCount][CityCount])
{
	int currentcity = Ant_temp->tour[Ant_temp->tour_citycount - 1];//计算下一步先找到上一步所到的城市
	double temp = 0, sum_probability = 0;
	for (int i = 0; i < CityCount; i++)
	{
		if (Ant_temp->can_visit[i] == true)
			temp += pow((τ[currentcity][i]), α) * pow(1.0 / alldisarray[currentcity][i], β);
	}
	for (int i = 0; i < CityCount; i++)
	{
		if (Ant_temp->can_visit[i] == false)
			Ant_temp->select_probability[i] = 0;//已经到过的城市选择概率为0
		else
		{
			Ant_temp->select_probability[i] = pow((τ[currentcity][i]), α) * pow(1.0 / alldisarray[currentcity][i], β) / temp;//对于未到过的城市，则计算选择概率
			sum_probability += Ant_temp->select_probability[i];
		}
	}
	double r = random(0, sum_probability);//取概率区间的随机浮点数
	double p = 0;
	int nextcity = -1;
	for (int j = 0; j < CityCount; j++)
	{
		if (Ant_temp->can_visit[j] == true) p += Ant_temp->select_probability[j];
		if (p >= r)
		{
			nextcity = j; break;
		}
	}
	/*if (nextcity == -1)
	{
		temp = -1;
		for (int i = 0; i<CityCount; i++)
		{
			if (can_visit[i] == true)
				if (temp<pow((Map_City.τ[currentcity][i]), α)*pow(1.0 / Map_City.Distance[currentcity][i], β))
				{
					temp = pow((Map_City.τ[currentcity][i]), α)*pow(1.0 / Map_City.Distance[currentcity][i], β);
					nextcity = i;
				}
		}
	}*/
	Ant_Addcity(Ant_temp,nextcity);
}

void Ant_Build_Trip(solution_Ant* Ant_temp, double τ[CityCount][CityCount], double Deltτ[CityCount][CityCount], double alldisarray[CityCount][CityCount])
{
	for (int i = 0; i < CityCount; i++)
	{
		Ant_temp->can_visit[i] = true;
	}
	Ant_GetFirstCity(Ant_temp);
	while (Ant_temp->tour_citycount < CityCount)
	{
		if (Ant_temp->tour_citycount < CityCount) Ant_Next_City(Ant_temp, τ, Deltτ, alldisarray);//轮盘赌法选择下一个城市
		else if (Ant_temp->tour_citycount == CityCount - 1)
		{
			for (int i = 0; i < CityCount; i++)
				if (Ant_temp->can_visit[i] == true)
				{
					Ant_Addcity(Ant_temp,i);
					break;
				}//如果还剩下一个城市可以访问，那么这个城市就是最后一个城市，添加到蚂蚁旅行的城市上
		}
	}
	Ant_temp->tour[CityCount] = Ant_temp->tour[0];//蚂蚁旅行的最后一个城市
}

void Ant_UpdateTourLength(solution_Ant* Ant_temp,double alldisarray[CityCount][CityCount])//更新旅行路径长度的函数
{
	for (int i = 0; i < CityCount - 1; i++)
	{
		Ant_temp->tour_length += alldisarray[Ant_temp->tour[i]][Ant_temp->tour[i + 1]];
	}
	Ant_temp->tour_length += alldisarray[Ant_temp->tour[CityCount - 1]][Ant_temp->tour[0]];
}