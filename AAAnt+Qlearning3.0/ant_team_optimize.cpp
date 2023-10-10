#include"main.h"
#include"cal_distance.h"


void inter_swap(solution_Ant_team *Ant_Team,double alldisarray[CityCount][CityCount], read_city RC[CityCount],read_order OC)
{
	solution_Ant_team ant_tmp;
	 //Ant_Team=&ant_tmp;
	for (int i = 0; i <= CarCount; i++)
	{
		ant_tmp.ant_team[i] = Ant_Team->ant_team[i];
		ant_tmp.ant_team_totallen = 0.0;
		ant_tmp.total_delay = 0.0;
		ant_tmp.ant_team[i].ant_delay = 0.0;
	}
	for (int j = 0; j < CityCount; j++)
	{
		ant_tmp.tour_punish[j] = 0.0;
	}
	for (int i = 0; i <= CarCount; i++)
	{
		for (int j = 1; j < Ant_Team->ant_team[i].tour_citycount-1; j++)
		{
			int temp_pos = ant_tmp.ant_team[i].tour[j];
			ant_tmp.ant_team[i].tour[j] = ant_tmp.ant_team[i].tour[j + 1];
			ant_tmp.ant_team[i].tour[j + 1] = temp_pos;


			ant_tmp.ant_team[i].tour_length = calculateSumOfDistance(ant_tmp.ant_team[i], alldisarray);
			ant_tmp.ant_team_totallen += calculateSumOfDistance(ant_tmp.ant_team[i], alldisarray);
			calculatetimepuinish(&ant_tmp, alldisarray, RC,OC);
			for (int a = 0; a < CityCount; a++)
			{
				ant_tmp.total_delay += ant_tmp.tour_punish[a];
			}
			if ((ant_tmp.ant_team_totallen * 0.8 + ant_tmp.total_delay * 0.2) <= (Ant_Team->ant_team_totallen * 0.8 + Ant_Team->total_delay * 0.2))
			{
				Ant_Team = &ant_tmp;
				break;
			}
		}
		//ant_tmp.ant_team[i] = Ant_Team->ant_team[i];
	}
}