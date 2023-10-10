#include"main.h"
void UpdatePheromones(double τ[CityCount][CityCount], double Deltτ[CityCount][CityCount], solution_Ant ant[AntCount])//更新信息素的函数
{
	for (int i = 0; i < AntCount; i++)
	{
		for (int j = 0; j < CityCount - 1; j++)
		{
			Deltτ[ant[i].tour[j]][ant[i].tour[j + 1]] += Q / ant[i].tour_length;
			Deltτ[ant[i].tour[j + 1]][ant[i].tour[j]] += Q / ant[i].tour_length;
		}
		Deltτ[ant[i].tour[CityCount - 1]][ant[i].tour[0]] += Q / ant[i].tour_length;
		Deltτ[ant[i].tour[0]][ant[i].tour[CityCount - 1]] += Q / ant[i].tour_length;
	}
	for (int i = 0; i < CityCount; i++)
	{
		for (int j = 0; j < CityCount; j++)
		{
			τ[i][j] = (1 - ρ) * τ[i][j] + Deltτ[i][j];
			Deltτ[i][j] = 0;
		}
	}
}

void UpdatePheromones_team(double τ[CityCount][CityCount], double Deltτ[CityCount][CityCount], solution_Ant_team ant)//更新团队信息素的函数
{
	for (int i = 0; i <= CarCount; i++)
	{
		if (ant.ant_team[i].tour_length > 0.0)
		{
			//for (int j = 0; j < CityCount - 1; j++)
			for (int j = 0; j < ant.ant_team[i].tour_citycount - 1; j++)
			{
				Deltτ[ant.ant_team[i].tour[j]][ant.ant_team[i].tour[j + 1]] += W_Q / (ant.ant_team[i].tour_length + ant.tour_punish[ant.ant_team[i].tour[j + 1]]);
				Deltτ[ant.ant_team[i].tour[j + 1]][ant.ant_team[i].tour[j]] += W_Q / (ant.ant_team[i].tour_length + ant.tour_punish[ant.ant_team[i].tour[j]]);
			}
			//Deltτ[ant.ant_team[i].tour[CityCount - 1]][ant.ant_team[i].tour[0]] += (Q+1)/ (ant.ant_team[i].tour_length+ant.tour_punish[ant.ant_team[i].tour[0]]);
			//Deltτ[ant.ant_team[i].tour[0]][ant.ant_team[i].tour[CityCount - 1]] += (Q +1)/ (ant.ant_team[i].tour_length +ant.tour_punish[ant.ant_team[i].tour[CityCount - 1]]);
		}
	}
	double max_AQ = 0.0;
	for (int i = 0; i < CityCount; i++)
	{
		for (int j = 0; j < CityCount; j++)
		{
			for (int a = 0; a < CityCount; a++)
			{
				if (τ[j][a] > max_AQ)
				{
					max_AQ = τ[j][a];
				}
			}
			τ[i][j] = (1 - alfh_Q) * τ[i][j] + alfh_Q * (Deltτ[i][j] + gama_Q * max_AQ);
			//τ[i][j] = (1 - ρ) * τ[i][j] + Deltτ[i][j];
			Deltτ[i][j] = 0;
			max_AQ = 0.0;
		}
		max_AQ = 0.0;
	}
}