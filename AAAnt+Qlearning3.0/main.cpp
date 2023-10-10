#include"main.h"
#include"cal_distance.h"
#include"ant_operator.h"
#include"ant_team_operator.h"
#include"ant_team_optimize.h"
void UpdatePheromones(double τ[CityCount][CityCount], double Deltτ[CityCount][CityCount], solution_Ant ant[AntCount]);//更新信息素的函数
void UpdatePheromones_team(double τ[CityCount][CityCount], double Deltτ[CityCount][CityCount], solution_Ant_team ant);//更新团队信息素的函数
int main()
{
	string problem_paths[] = { "G:\\蚁群算法\\readdata\\25\\C101.txt", "G:\\蚁群算法\\readdata\\25\\R101.txt", "G:\\蚁群算法\\readdata\\25\\RC101.txt",
	"G:\\蚁群算法\\readdata\\25\\C201.txt", "G:\\蚁群算法\\readdata\\25\\R201.txt", "G:\\蚁群算法\\readdata\\25\\RC201.txt",
	"G:\\蚁群算法\\readdata\\50\\C101.txt", "G:\\蚁群算法\\readdata\\50\\R101.txt", "G:\\蚁群算法\\readdata\\50\\RC101.txt",
	"G:\\蚁群算法\\readdata\\50\\C201.txt", "G:\\蚁群算法\\readdata\\50\\R201.txt", "G:\\蚁群算法\\readdata\\50\\RC201.txt",
	"G:\\蚁群算法\\readdata\\100\\C101.txt", "G:\\蚁群算法\\readdata\\100\\R101.txt", "G:\\蚁群算法\\readdata\\100\\RC101.txt",
	"G:\\蚁群算法\\readdata\\100\\C201.txt", "G:\\蚁群算法\\readdata\\100\\R201.txt", "G:\\蚁群算法\\readdata\\100\\RC201.txt"
	};
	string order_paths[] = { "G:\\蚁群算法\\程序\\ADV\\order\\25.txt", "G:\\蚁群算法\\程序\\ADV\\order\\25.txt", "G:\\蚁群算法\\程序\\ADV\\order\\25.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\25.txt","G:\\蚁群算法\\程序\\ADV\\order\\25.txt","G:\\蚁群算法\\程序\\ADV\\order\\25.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\50.txt", "G:\\蚁群算法\\程序\\ADV\\order\\50.txt", "G:\\蚁群算法\\程序\\ADV\\order\\50.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\50.txt","G:\\蚁群算法\\程序\\ADV\\order\\50.txt","G:\\蚁群算法\\程序\\ADV\\order\\50.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\100.txt", "G:\\蚁群算法\\程序\\ADV\\order\\100.txt", "G:\\蚁群算法\\程序\\ADV\\order\\100.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\100.txt","G:\\蚁群算法\\程序\\ADV\\order\\100.txt","G:\\蚁群算法\\程序\\ADV\\order\\100.txt"
};
	read_city RC[CityCount];

	read_order OC;

	ifstream tryfile;
	//tryfile.open("G:/蚁群算法/mat31.txt", ios::in);
	//tryfile.open("G:/蚁群算法/readdata/25/C101.txt", ios::in);
	tryfile.open(problem_paths[0], ios::in);
	if (!tryfile.is_open())
		std::cerr << "open error";
	if (!tryfile)
		std::cerr << "open error1";
	for (int i = 0; i < CityCount; i++)
	{
		//for (int j = 0; j < 7 ;j++)
		//{
			//tryfile >> C[i][j];
			tryfile >> RC[i].city_id >> RC[i].C_x >> RC[i].C_y >> RC[i].tour_capacity >> RC[i].Early_time >> RC[i].Last_time >> RC[i].punish;
		//}

	}
	tryfile.close();

	ifstream tryfileorder;
	//tryfile.open("G:/蚁群算法/mat31.txt", ios::in);
	//tryfile.open("G:/蚁群算法/readdata/25/C101.txt", ios::in);
	tryfileorder.open(order_paths[0], ios::in);
	if (!tryfileorder.is_open())
		std::cerr << "open error";
	if (!tryfileorder)
		std::cerr << "open error1";

	
		tryfileorder >> OC.car_id_num;
for (int j = 0; j < CarCount; j++)
	{
		tryfileorder >> OC.car_arrive[j];
		tryfileorder >> OC.point_num[j];
		for (int i = 0; i < OC.point_num[j]; i++)
		{
			tryfileorder >> OC.point_index[j][i];
		}
	}
	tryfileorder.close();

	//cout<< OC.car_id_num<<endl;
	//for (int j = 0; j < CarCount; j++)
	//{
	//	cout<< OC.car_arrive[j]<<endl;
	//	cout << OC.point_num[j] << endl;
	//	for (int i = 0; i < OC.point_num[j]; i++)
	//	{
	//		cout<< OC.point_index[j][i]<<"    ";
	//	}
	//	cout << endl;
	//}
	double max_dis = 0.0;
	solution_Ant ant[AntCount];
	double alldisarray[CityCount][CityCount];
	for (int i = 0; i < CityCount; i++)
	{
		for (int j = 0; j < CityCount; j++)
		{
	     alldisarray[i][j] = calculateTwoDistance(RC, i, j);
		alldisarray[j][i] = alldisarray[i][j];
		if (i == j)
		{
			alldisarray[i][j] = 0;
		}
		if (max_dis <= alldisarray[i][j])
		{
			max_dis = alldisarray[i][j];
		}
			//cout << alldisarray[i][j]<<"    ";
		}
		//cout << endl;
	}

	for (int xun = 0; xun < 1000; xun++)
	{
		double τ[CityCount][CityCount];//信息素矩阵
		double Deltτ[CityCount][CityCount];//信息素变化量矩阵
		for (int i = 0; i < CityCount; i++)
		{
			for (int j = 0; j < CityCount; j++)
			{
				τ[i][j] = 1;
				Deltτ[i][j] = 0;
			}
		}

		int MAX_GEN = 250;
		//double global_tourlength = 10e9, Ljia = DBL_MAX;
		solution_Ant Tjia;//表示蚁群优化算法最终发现的最短路径
		Tjia.tour_length = 10e9;
		//首先对城市地图进行初始化
		solution_Ant temp_tour;
		//double total_delay = 0.0;
		for (int iteratorcishu = 0; iteratorcishu < MAX_GEN; iteratorcishu++)
		{
			for (int k = 0; k < AntCount; k++)
			{
				Ant_Clear(&ant[k]);
				Ant_Build_Trip(&ant[k], τ, Deltτ, alldisarray);
				Ant_UpdateTourLength(&ant[k], alldisarray);//计算蚂蚁k所发现路径Tk的长度Lk
				if (ant[k].tour_length < Tjia.tour_length)
				{
					Tjia = ant[k];
				}
			}
			//找到最短的路径长度，放到temp里
			double temp = ant[0].tour_length;
			for (int i = 0; i < CityCount; i++) temp_tour.tour[i] = ant[0].tour[i];
			for (int i = 0; i < AntCount; i++)
			{
				if (temp > ant[i].tour_length)
				{
					temp = ant[i].tour_length;
					for (int j = 0; j < CityCount; j++)
						temp_tour.tour[j] = ant[i].tour[j];
				}
			}
			if (temp < Tjia.tour_length)
			{
				Tjia.tour_length = temp;
				Tjia = temp_tour;
			}
			//std::cout << "第" << iteratorcishu << "次迭代的最短距离：" << Tjia.tour_length << endl;
			UpdatePheromones(τ, Deltτ, ant);
			for (int i = 0; i < AntCount; i++)
			{
				Ant_Clear(&ant[i]);
			}
		}
		//std::cout << "最短路径长度为：" << Tjia.tour_length << endl;
		//system("Pause");
		//for (int i = 0; i < CityCount; i++)
		//{
		//	for (int j = 0; j < CityCount; j++)
		//	{
		//		cout << τ[i][j] << "      ";
		//	}
		//	cout << endl;
		//}
		solution_Ant_team sol_ant_team[CityCount];
		solution_Ant_team best_ant_t;
		//best_ant_t.ant_team[0] = { 0, 21, 25, 18, 11, 4, 2 };
		//best_ant_t.ant_team[1] = { 0, 5, 3, 1, 6, 9, 8, 7, 23, 22 };
		//best_ant_t.ant_team[2] = {0, 20, 24, 13, 17, 19, 15, 16, 14, 12, 10};
		//for (int j = 0; j <= CarCount; j++)
		//{
		//	calculatetimewindow(&best_ant_t, alldisarray, RC);
		//	calculatetimepuinish(&best_ant_t, alldisarray, RC);
		//	best_ant_t.ant_team[j].tour_length = calculateSumOfDistance(best_ant_t.ant_team[j], alldisarray);
		//	best_ant_t.ant_team_totallen += calculateSumOfDistance(best_ant_t.ant_team[j], alldisarray);
		//	UpdatePheromones_team(τ, Deltτ, best_ant_t);
		//}
		best_ant_t.ant_team_totallen = best_ant_t.total_delay = 10e9;
		int count = 0;
		while (count <= MAX_GEN + 100)
		{
			for (int j = 0; j < CityCount; j++)
			{
				for (int i = 0; i <= CarCount; i++)
				{
					Ant_Clear(&sol_ant_team[j].ant_team[i]);
				}
				Antteam_Clear(&sol_ant_team[j]);
			}

			for (int k = 0; k < CityCount; k++)
			{
				for (int i = 0; i < CityCount; i++)//判断所有点是否走完
				{
					while (sol_ant_team[k].ant_team[0].can_visit[i] == true)
					{
						Antteam_Choice_Next(&sol_ant_team[k], τ, alldisarray, RC);
					}
				}
				inter_swap(&sol_ant_team[k], alldisarray, RC,OC);
				Antteam_Clear_delay(&sol_ant_team[k]);
				//calculatetimewindow(&sol_ant_team[k], alldisarray,RC);
				calculatetimepuinish(&sol_ant_team[k], alldisarray, RC,OC);
				for (int j = 0; j <= CarCount; j++)
				{
					//inter_swap(&sol_ant_team[k], alldisarray, RC);
					//calculatetimewindow(&sol_ant_team[k], alldisarray,RC);
					//calculatetimepuinish(& sol_ant_team[k], alldisarray, RC);
					sol_ant_team[k].ant_team[j].tour_length = calculateSumOfDistance(sol_ant_team[k].ant_team[j], alldisarray);
					sol_ant_team[k].ant_team_totallen += calculateSumOfDistance(sol_ant_team[k].ant_team[j], alldisarray);
					//UpdatePheromones_team(τ, Deltτ, sol_ant_team[k]);
				}
				UpdatePheromones_team(τ, Deltτ, sol_ant_team[k]);
				//			cout << sol_ant_team[k].ant_team_totallen << "       ";
							/*cout<<"---------------------------------------------------------------------------" << endl;
							for (int i = 0; i < CityCount; i++)
							{
								for (int j = 0; j < CityCount; j++)
								{
									cout << τ[i][j] << " ";
								}
								cout << endl;
							}*/
				for (int a = 0; a < CityCount; a++)
				{
					sol_ant_team[k].total_delay += sol_ant_team[k].tour_punish[a];
				}
				//inter_swap(&sol_ant_team[k], alldisarray, RC);
				if ((sol_ant_team[k].ant_team_totallen * 0.8 + sol_ant_team[k].total_delay * 0.2) < (best_ant_t.ant_team_totallen * 0.8 + best_ant_t.total_delay * 0.2))
					//if (sol_ant_team[k].ant_team_totallen  < best_ant_t.ant_team_totallen )
				{
					best_ant_t = sol_ant_team[k];
					//cout << best_ant_t.ant_team_totallen << "     +    " << best_ant_t.total_delay << "==" << (best_ant_t.ant_team_totallen * 0.8 + best_ant_t.total_delay * 0.2) << endl;
					UpdatePheromones_team(τ, Deltτ, best_ant_t);
					//inter_swap(&best_ant_t, alldisarray, RC);
					//cout << best_ant_t.ant_team_totallen << "     +    " << best_ant_t.total_delay << "==" << (best_ant_t.ant_team_totallen * 0.8 + best_ant_t.total_delay * 0.2) << endl;
				}
			}
			//cout << best_ant_t.ant_team_totallen<<"     +    "<<best_ant_t.total_delay <<"=="<<(best_ant_t.ant_team_totallen * 0.8 + best_ant_t.total_delay * 0.2) << endl;
			for (int j = 0; j < CityCount; j++)
			{
				for (int i = 0; i <= CarCount; i++)
				{
					Ant_Clear(&sol_ant_team[j].ant_team[i]);
				}
				Antteam_Clear(&sol_ant_team[j]);
				Antteam_Clear_delay(&sol_ant_team[j]);
			}
			count++;

		}
		cout << best_ant_t.ant_team_totallen << "          " << best_ant_t.total_delay << "      " << (best_ant_t.ant_team_totallen * 0.8*(max_dis/1500.0) + best_ant_t.total_delay * 0.2* (max_dis / 1500.0)) << endl;
	}
	return 0;
}

