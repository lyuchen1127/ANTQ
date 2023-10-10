#include"main.h"
int random(int uper);//����һ����0��������������������

double  random(int low, double uper);//����ĳ��������������ĺ���
void Ant_Initial(solution_Ant *Ant_temp)//���ϵĹ��캯��
{
	Ant_temp->tour_length  = 0;
	
	Ant_temp->tour_citycount = 0;//��������й��ĳ�������Ϊ0
	for (int i = 0; i < CityCount; i++)
	{
		Ant_temp->can_visit[i] = true;//ÿ�����ж����Է���
		Ant_temp-> select_probability[i] = 0;//ѡ��������еĸ���Ϊ0
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

void Ant_Next_City(solution_Ant* Ant_temp,double ��[CityCount][CityCount],double Delt��[CityCount][CityCount], double alldisarray[CityCount][CityCount])
{
	int currentcity = Ant_temp->tour[Ant_temp->tour_citycount - 1];//������һ�����ҵ���һ�������ĳ���
	double temp = 0, sum_probability = 0;
	for (int i = 0; i < CityCount; i++)
	{
		if (Ant_temp->can_visit[i] == true)
			temp += pow((��[currentcity][i]), ��) * pow(1.0 / alldisarray[currentcity][i], ��);
	}
	for (int i = 0; i < CityCount; i++)
	{
		if (Ant_temp->can_visit[i] == false)
			Ant_temp->select_probability[i] = 0;//�Ѿ������ĳ���ѡ�����Ϊ0
		else
		{
			Ant_temp->select_probability[i] = pow((��[currentcity][i]), ��) * pow(1.0 / alldisarray[currentcity][i], ��) / temp;//����δ�����ĳ��У������ѡ�����
			sum_probability += Ant_temp->select_probability[i];
		}
	}
	double r = random(0, sum_probability);//ȡ������������������
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
				if (temp<pow((Map_City.��[currentcity][i]), ��)*pow(1.0 / Map_City.Distance[currentcity][i], ��))
				{
					temp = pow((Map_City.��[currentcity][i]), ��)*pow(1.0 / Map_City.Distance[currentcity][i], ��);
					nextcity = i;
				}
		}
	}*/
	Ant_Addcity(Ant_temp,nextcity);
}

void Ant_Build_Trip(solution_Ant* Ant_temp, double ��[CityCount][CityCount], double Delt��[CityCount][CityCount], double alldisarray[CityCount][CityCount])
{
	for (int i = 0; i < CityCount; i++)
	{
		Ant_temp->can_visit[i] = true;
	}
	Ant_GetFirstCity(Ant_temp);
	while (Ant_temp->tour_citycount < CityCount)
	{
		if (Ant_temp->tour_citycount < CityCount) Ant_Next_City(Ant_temp, ��, Delt��, alldisarray);//���̶ķ�ѡ����һ������
		else if (Ant_temp->tour_citycount == CityCount - 1)
		{
			for (int i = 0; i < CityCount; i++)
				if (Ant_temp->can_visit[i] == true)
				{
					Ant_Addcity(Ant_temp,i);
					break;
				}//�����ʣ��һ�����п��Է��ʣ���ô������о������һ�����У���ӵ��������еĳ�����
		}
	}
	Ant_temp->tour[CityCount] = Ant_temp->tour[0];//�������е����һ������
}

void Ant_UpdateTourLength(solution_Ant* Ant_temp,double alldisarray[CityCount][CityCount])//��������·�����ȵĺ���
{
	for (int i = 0; i < CityCount - 1; i++)
	{
		Ant_temp->tour_length += alldisarray[Ant_temp->tour[i]][Ant_temp->tour[i + 1]];
	}
	Ant_temp->tour_length += alldisarray[Ant_temp->tour[CityCount - 1]][Ant_temp->tour[0]];
}