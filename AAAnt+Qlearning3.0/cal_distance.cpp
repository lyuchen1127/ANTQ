#include"main.h"
//int ChooseNextNode(int currentNode, int visitedNode[], double alldisarray[CityCount][CityCount]);
void Antteam_Clear_delay(solution_Ant_team* Ant_team_temp);




double calculateTwoDistance(read_city RC[CityCount], int i, int j)
{
	return sqrt(pow((RC[i].C_x - RC[j].C_x), 2.0) + pow((RC[i].C_y - RC[j].C_y), 2.0));
}

double calculateSumOfDistance(solution_Ant ant_temp, double alldisarray[CityCount][CityCount])
{
	double sum = 0;
	for (int i = 0; i < CityCount-1; i++)
	{
		int row = ant_temp.tour[i];
		int col = ant_temp.tour[i+1];
		sum += alldisarray[row][col];
	}
	sum += alldisarray[ant_temp.tour[CityCount - 1]][ant_temp.tour[0]];
	return sum;
}

void Check_value(solution_Ant_team *ant_temp, double alldisarray[CityCount][CityCount],read_city RC[CityCount])
{
	for (int i = 0; i <= CarCount; i++)
	{
		for (int j = 1; j < ant_temp->ant_team[i].tour_citycount; j++)
		{
			if (ant_temp->ant_team[i].tour[j] == 0)
			{
				for (int t = j; t < ant_temp->ant_team[i].tour_citycount; t++)
				{
					int temp_pos = ant_temp->ant_team[i].tour[t];
					ant_temp->ant_team[i].tour[t] = ant_temp->ant_team[i].tour[t + 1];
					ant_temp->ant_team[i].tour[t + 1] = temp_pos;
				}
				ant_temp->ant_team[i].tour_citycount = ant_temp->ant_team[i].tour_citycount - 1;

				for (int a = 0; a <= CarCount; a++)
				{
					ant_temp->ant_team[a].charging_ant = 8000.0;
					ant_temp->ant_team[a].ant_capacity = Max_capacity;
					for (int b = 0; b < CityCount-1;b++)
					{
						ant_temp->ant_team[a].ant_capacity = ant_temp->ant_team[a].ant_capacity - RC[ant_temp->ant_team[a].tour[b]].tour_capacity;
						ant_temp->ant_team[a].charging_ant= ant_temp->ant_team[a].charging_ant-
							(fabs(alldisarray[ant_temp->ant_team[a].tour[b]][b+1]) * (ant_temp->ant_team[a].ant_capacity / Max_capacity));
					}
				}
			}
		}
	}
}

void calculatetimewindow(solution_Ant_team *ant_temp, double alldisarray[CityCount][CityCount], read_city RC[CityCount])
{
	Check_value(ant_temp, alldisarray,RC);
	double sum = 0.0;
	for (int j = 0; j <= CarCount; j++)
	{
		for (int i = 1; i < ant_temp->ant_team[j].tour_citycount; i++)
		{
			int row = ant_temp->ant_team[j].tour[i-1];
			int col = ant_temp->ant_team[j].tour[i];
			sum += alldisarray[row][col];
			ant_temp->tour_time[ant_temp->ant_team[j].tour[i]] = sum;
		}
		sum = 0.0;
	}
	//sum += alldisarray[ant_temp.tour[CityCount - 1]][ant_temp.tour[0]];
}

void calculatetimepuinish(solution_Ant_team* ant_temp, double alldisarray[CityCount][CityCount], read_city RC[CityCount],read_order OC)
{
	Check_value(ant_temp, alldisarray, RC);
	Antteam_Clear_delay(ant_temp);
	double sum = 0.0;
	double tour_window_time[CityCount];
	int bachcount = 0;
	for (int a = 0; a <= CarCount; a++)
	{
		for (int i = 0; i < OC.car_id_num; i++)
		{
			for (int j = 0; j < OC.point_num[i]; j++)
			{
				ant_temp->ant_team[a].ant_order_start[OC.point_index[i][j]] = OC.car_arrive[i];
				ant_temp->ant_team[a].ant_order_bach = bachcount;
			}
		}
		bachcount++;
	}
	//cout << endl;
	for (int a = 0; a <= CarCount; a++)
	{
		for (int b = 0; b < ant_temp->ant_team[a].tour_citycount; b++)
		{
			if (ant_temp->ant_team[a].ant_order_maxdelay <= ant_temp->ant_team[a].ant_order_start[ant_temp->ant_team[a].tour[b]])
			{
				ant_temp->ant_team[a].ant_order_maxdelay = ant_temp->ant_team[a].ant_order_start[ant_temp->ant_team[a].tour[b]];
			}
		}
	}
	for (int i = 0; i <=CarCount; i++)
	{
		ant_temp->ant_team[i].ant_delay = 0.0;
		tour_window_time[0]=0.0;
		sum=ant_temp->ant_team[i].ant_order_maxdelay;
		for (int j = 1; j < ant_temp->ant_team[i].tour_citycount; j++)
		{
			int row = ant_temp->ant_team[i].tour[j - 1];
			int col = ant_temp->ant_team[i].tour[j];
			sum += alldisarray[row][col];
			if (sum <= RC[ant_temp->ant_team[i].tour[j]].Early_time)
			{
				tour_window_time[ant_temp->ant_team[i].tour[j]] = RC[ant_temp->ant_team[i].tour[j]].Early_time;
				sum= RC[ant_temp->ant_team[i].tour[j]].Early_time;
				ant_temp->ant_team[i].ant_delay += 0.0;
			}
			else {
				if (sum <= RC[ant_temp->ant_team[i].tour[j]].Last_time)
				{
					tour_window_time[ant_temp->ant_team[i].tour[j]] = sum;
					ant_temp->ant_team[i].ant_delay += 0.0;
				}
				else
				{
					ant_temp->tour_punish[ant_temp->ant_team[i].tour[j]] = sum - RC[ant_temp->ant_team[i].tour[j]].Last_time;
					ant_temp->ant_team[i].ant_delay += sum - RC[ant_temp->ant_team[i].tour[j]].Last_time;
				}
			}
			//sum = 0.0;
		}
		sum = 0.0;
	}
	//sum = 0.0;
	/*cout << "punishi:" << endl;
	for (int i = 0; i < CityCount; i++)
	{
		cout << ant_temp->tour_punish[i]<<" ,";
	}
	cout << endl;*/
}

