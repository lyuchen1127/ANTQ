#include"main.h"
int random(int uper);//返回一个从0到最大随机数的任意整数

double  random(int low, double uper);//生成某个区间内随机数的函数

double max(double x, double y)//定义max函数形式参数x，y为整形
{
	double z;
	if (x < y)
		z = y;//如果x>y成立那么将y的值赋值给y
	else
		z = x;//若上述不成立那么将x的值赋值给z
	return (z);//将z值作为max函数值，返回调用max函数位置
}

void Antteam_Clear(solution_Ant_team* Ant_team_temp)
{
	for (int i = 0; i <= CarCount; i++)
	{
		for (int j = 0; j < CityCount; j++)
		{
			Ant_team_temp->ant_team[i].tour_length = 0.0;
			Ant_team_temp->ant_team[i].tour[j] = 0;
			Ant_team_temp->tour_time[j] = 0.0;
			Ant_team_temp->tour_punish[j] = 0.0;
		}
		Ant_team_temp->ant_team[i].tour[CityCount] = 0;
		Ant_team_temp->ant_team[i].tour[0] = 0;
		Ant_team_temp->ant_team[i].can_visit[0] = false;
		Ant_team_temp->ant_team[i].can_visit[CityCount] = false;
		Ant_team_temp->ant_team[i].tour_citycount =1;

		Ant_team_temp->total_delay = 0.0;
		Ant_team_temp->ant_team[i].ant_delay = 0.0;
		Ant_team_temp->ant_team[i].ant_capacity = Max_capacity;
		Ant_team_temp->ant_team[i].charging_ant = 10000.0;
	}
	Ant_team_temp->ant_team_totallen = 0.0;
	Ant_team_temp->total_delay = 0.0;
}

void Antteam_Clear_delay(solution_Ant_team* Ant_team_temp)
{
	Ant_team_temp->total_delay = 0.0;
	for (int b = 0; b <= CarCount; b++)
	{
		Ant_team_temp->ant_team[b].ant_delay = 0.0;
	}
	for (int c = 0; c < CityCount; c++)
	{
		Ant_team_temp->tour_punish[c] = 0.0;
	}
}

void Antteam_Choice_Next(solution_Ant_team* Ant_team_temp, double τ[CityCount][CityCount], double alldisarray[CityCount][CityCount], read_city RC[CityCount])
{
	int currentcity[CarCount+1];//计算下一步先找到上一步所到的城市
	double temp[CarCount+1];
	double sum_probability[CarCount+1];
	double currenttime[CarCount + 1];

	for (int i = 0; i <= CarCount; i++)
	{
		currentcity[i] = Ant_team_temp->ant_team[i].tour[Ant_team_temp->ant_team[i].tour_citycount - 1];
		temp[i] = 0.0;
		sum_probability[i] = 0.0;
		currenttime[i] = Ant_team_temp->ant_team[i].start_service_time;
	}

	for (int i = 0; i <= CarCount; i++)
	{
		for (int j = 0; j < CityCount; j++)
		{
			if (Ant_team_temp->ant_team[i].can_visit[j] == false)
			{
				Ant_team_temp->ant_team[i].select_probability[j] = 0;
			}
			else {
				Ant_team_temp->ant_team[i].select_probability[j] = τ[Ant_team_temp->ant_team[i].tour[Ant_team_temp->ant_team[i].tour_citycount - 1]][j]
					+1/(max(currenttime[i], fabs(RC[j].Early_time - Ant_team_temp->ant_team[i].start_service_time)));
				sum_probability[i] += Ant_team_temp->ant_team[i].select_probability[j];
			}
		}
	}
	double r[CarCount+1]; //取概率区间的随机浮点数
	double p[CarCount+1];
	int nextcity[CarCount+1]; 
	for (int i = 0; i <= CarCount; i++)
	{
		r[i] = random(0, sum_probability[i]);
		p[i] = 0;
		nextcity[i] = -1;
	}
	for (int i = 0; i <= CarCount; i++)
	{
		for (int j = 0; j < CityCount; j++)
		{
			if (Ant_team_temp->ant_team[i].can_visit[j] == true) p[i] += Ant_team_temp->ant_team[i].select_probability[j];
			if (p[i] >= r[i])
			{
				nextcity[i] = j; break;
			}
		}
	}
	/*for (int i = 0; i < CarCount; i++)
	{
		cout << nextcity[i] << "    ";
	}
	cout << endl;*/
	double Pop_lunpan[CarCount+1] = { 0.0 };
	double sum_lunpan = 0.0;
	int all_can_not = 0;
	for (int i = 0; i <= CarCount; i++)
	{
		if (Ant_team_temp->ant_team[i].charging_ant <= (alldisarray[nextcity[i]][Ant_team_temp->ant_team[i].tour[0]]
			+ alldisarray[Ant_team_temp->ant_team[i].tour[Ant_team_temp->ant_team[i].tour_citycount - 1]][nextcity[i]])
			|| Ant_team_temp->ant_team[i].ant_capacity < 1)
		{
			Pop_lunpan[i] = 0;
			all_can_not ++;
		}
		else
		{
				Pop_lunpan[i] = 1 / (alldisarray[Ant_team_temp->ant_team[i].tour[Ant_team_temp->ant_team[i].tour_citycount - 1]][nextcity[i]] +fabs( RC[nextcity[i]].Early_time - Ant_team_temp->ant_team[i].start_service_time));
				all_can_not=0;
				//Pop_lunpan[CarCount] = 0;
		}
		sum_lunpan += Pop_lunpan[i];
	}

	double rand_c=random(0, 1);
	double rand_p = 0.0;
	double rand_r = random(0, sum_probability[CarCount]);

	for (int i = 0; i < CarCount; i++)
	{
		//if (all_can_not >= CarCount)
		if(sum_lunpan-Pop_lunpan[CarCount]==0)
		{
				for (int j = 0; j < CityCount; j++)
			{
					if (Ant_team_temp->ant_team[CarCount].can_visit[j] == true)
					{
						rand_p += Ant_team_temp->ant_team[CarCount].select_probability[j];
						if (rand_p >= rand_r)
						{
							Ant_team_temp->ant_team[CarCount].tour[Ant_team_temp->ant_team[CarCount].tour_citycount] = j;
							//Ant_team_temp->ant_team[CarCount].charging_ant = Ant_team_temp->ant_team[CarCount].charging_ant- fabs(alldisarray[Ant_team_temp->ant_team[CarCount].tour[Ant_team_temp->ant_team[CarCount].tour_citycount - 1]][Ant_team_temp->ant_team[CarCount].tour[Ant_team_temp->ant_team[CarCount].tour_citycount]]);
							Ant_team_temp->ant_team[CarCount].charging_ant = Ant_team_temp->ant_team[CarCount].charging_ant -
								(fabs(alldisarray[Ant_team_temp->ant_team[CarCount].tour[Ant_team_temp->ant_team[CarCount].tour_citycount - 1]][j]) *(Ant_team_temp->ant_team[CarCount].ant_capacity/ Max_capacity)) ;
							//cout << Ant_team_temp->ant_team[CarCount].ant_capacity / Max_capacity << endl;
							Ant_team_temp->ant_team[CarCount].start_service_time = max(currenttime[CarCount] + alldisarray[Ant_team_temp->ant_team[CarCount].tour[Ant_team_temp->ant_team[CarCount].tour_citycount - 1]][j], RC[j].Early_time);
							Ant_team_temp->ant_team[CarCount].tour_citycount ++;
							for (int t = 0; t <= CarCount; t++)
							{
								//Ant_team_temp->ant_team[t].can_visit[Ant_team_temp->ant_team[CarCount].tour[Ant_team_temp->ant_team[CarCount].tour_citycount]] = false;
								Ant_team_temp->ant_team[t].can_visit[j] = false;
							}
							Ant_team_temp->ant_team[CarCount].ant_capacity= Ant_team_temp->ant_team[CarCount].ant_capacity - RC[j].tour_capacity;
							//Ant_team_temp->ant_team[CarCount].tour_citycount+=1;
							all_can_not = 0;
							break;
						}
					}
			}
					/*Ant_team_temp->ant_team[CarCount].charging_ant = Ant_team_temp->ant_team[CarCount].charging_ant 
						- fabs(alldisarray[Ant_team_temp->ant_team[CarCount].tour[Ant_team_temp->ant_team[CarCount].tour_citycount - 1]][Ant_team_temp->ant_team[CarCount].tour[Ant_team_temp->ant_team[CarCount].tour_citycount]]);
					for (int t = 0; t <= CarCount; t++)
					{
						Ant_team_temp->ant_team[t].can_visit[Ant_team_temp->ant_team[CarCount].tour[Ant_team_temp->ant_team[CarCount].tour_citycount]] = false;
					}
					Ant_team_temp->ant_team[CarCount].ant_capacity--;
					Ant_team_temp->ant_team[CarCount].tour_citycount++;
					all_can_not = 0;
					break;*/
	    }
		else
		{
			//Pop_lunpan[CarCount] = 0.0;
			all_can_not = 0;
			rand_c -= Pop_lunpan[i] / (sum_lunpan-Pop_lunpan[CarCount]);
			if (rand_c <= 0)
			{
				Ant_team_temp->ant_team[i].tour[Ant_team_temp->ant_team[i].tour_citycount] = nextcity[i];
				Ant_team_temp->ant_team[i].charging_ant = Ant_team_temp->ant_team[i].charging_ant 
					- (fabs(alldisarray[Ant_team_temp->ant_team[i].tour[Ant_team_temp->ant_team[i].tour_citycount- 1]][nextcity[i]]) * (Ant_team_temp->ant_team[i].ant_capacity / Max_capacity));
			//	cout << Ant_team_temp->ant_team[i].ant_capacity / Max_capacity << endl;
				Ant_team_temp->ant_team[i].tour_citycount= Ant_team_temp->ant_team[i].tour_citycount +1;
				Ant_team_temp->ant_team[i].start_service_time = max(currenttime[i] + alldisarray[Ant_team_temp->ant_team[i].tour[Ant_team_temp->ant_team[i].tour_citycount - 1]][nextcity[i]], RC[nextcity[i]].Early_time);
				for (int j = 0; j <= CarCount; j++)
				{
					Ant_team_temp->ant_team[j].can_visit[nextcity[i]] = false;
				}
				Ant_team_temp->ant_team[i].ant_capacity= Ant_team_temp->ant_team[i].ant_capacity - RC[nextcity[i]].tour_capacity;
				//Ant_team_temp->ant_team[i].tour_citycount+=1;
				break;
			}
		}
    }
	
}
