#include"main.h"
void UpdatePheromones(double ��[CityCount][CityCount], double Delt��[CityCount][CityCount], solution_Ant ant[AntCount])//������Ϣ�صĺ���
{
	for (int i = 0; i < AntCount; i++)
	{
		for (int j = 0; j < CityCount - 1; j++)
		{
			Delt��[ant[i].tour[j]][ant[i].tour[j + 1]] += Q / ant[i].tour_length;
			Delt��[ant[i].tour[j + 1]][ant[i].tour[j]] += Q / ant[i].tour_length;
		}
		Delt��[ant[i].tour[CityCount - 1]][ant[i].tour[0]] += Q / ant[i].tour_length;
		Delt��[ant[i].tour[0]][ant[i].tour[CityCount - 1]] += Q / ant[i].tour_length;
	}
	for (int i = 0; i < CityCount; i++)
	{
		for (int j = 0; j < CityCount; j++)
		{
			��[i][j] = (1 - ��) * ��[i][j] + Delt��[i][j];
			Delt��[i][j] = 0;
		}
	}
}

void UpdatePheromones_team(double ��[CityCount][CityCount], double Delt��[CityCount][CityCount], solution_Ant_team ant)//�����Ŷ���Ϣ�صĺ���
{
	for (int i = 0; i <= CarCount; i++)
	{
		if (ant.ant_team[i].tour_length > 0.0)
		{
			//for (int j = 0; j < CityCount - 1; j++)
			for (int j = 0; j < ant.ant_team[i].tour_citycount - 1; j++)
			{
				Delt��[ant.ant_team[i].tour[j]][ant.ant_team[i].tour[j + 1]] += W_Q / (ant.ant_team[i].tour_length + ant.tour_punish[ant.ant_team[i].tour[j + 1]]);
				Delt��[ant.ant_team[i].tour[j + 1]][ant.ant_team[i].tour[j]] += W_Q / (ant.ant_team[i].tour_length + ant.tour_punish[ant.ant_team[i].tour[j]]);
			}
			//Delt��[ant.ant_team[i].tour[CityCount - 1]][ant.ant_team[i].tour[0]] += (Q+1)/ (ant.ant_team[i].tour_length+ant.tour_punish[ant.ant_team[i].tour[0]]);
			//Delt��[ant.ant_team[i].tour[0]][ant.ant_team[i].tour[CityCount - 1]] += (Q +1)/ (ant.ant_team[i].tour_length +ant.tour_punish[ant.ant_team[i].tour[CityCount - 1]]);
		}
	}
	double max_AQ = 0.0;
	for (int i = 0; i < CityCount; i++)
	{
		for (int j = 0; j < CityCount; j++)
		{
			for (int a = 0; a < CityCount; a++)
			{
				if (��[j][a] > max_AQ)
				{
					max_AQ = ��[j][a];
				}
			}
			��[i][j] = (1 - alfh_Q) * ��[i][j] + alfh_Q * (Delt��[i][j] + gama_Q * max_AQ);
			//��[i][j] = (1 - ��) * ��[i][j] + Delt��[i][j];
			Delt��[i][j] = 0;
			max_AQ = 0.0;
		}
		max_AQ = 0.0;
	}
}