#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <ctime>
using namespace std;
#define CityCount   26
#define AntCount  26//城市数量和蚂蚁数量
#define CarCount  3//车辆数量
#define Max_capacity 2000.0

#define α  1
#define β  5
#define ρ  0.5
#define Q  1

#define W_Q 10
#define alfh_Q 0.1
#define fai_Q 1
#define beta_Q 2
#define gama_Q 0.3

struct read_city
{
	int city_id;
	//double C[CityCount][2];
	double C_x;
	double C_y;
	double Early_time;
	double Last_time;
	double tour_capacity;//该点的容量
	double punish;
};
struct read_order
{
	int car_id_num;
	//double C[CityCount][2];
	double car_arrive[CarCount];
	int point_num[CarCount];
	//int **point_index= (int**)malloc(sizeof(int*) *CarCount);
	//for (int i = 0; i < CarCount; i++)
	//{* point_index = (int*)malloc(sizeof(int) * point_num[i]);}
	int point_index[CarCount][CityCount] = {-1,-1,-1};
	//double punish;
};

struct solution_Ant
{
	int tour[CityCount + 1];//蚂蚁所构建路径的CityCount+1元数组
	bool can_visit[CityCount];//蚂蚁是否能够访问城市的n元布尔数组
	//double tour_time[CityCount + 1];

	int tour_citycount;//蚂蚁当前走过城市的数量
	double tour_length;//蚂蚁所走的路径长度tour_length
	//double tour_capacity;//该点的容量
	double select_probability[CityCount];//蚂蚁对各城市的选择概率数组
	double  ant_capacity; //车辆的容量
	double charging_ant;//车辆电量
	double start_service_time = 0.0;
    double ant_delay = 0.0;
	double ant_order_start[CityCount] = { 0.0 };
	int ant_order_bach;

	double ant_order_maxdelay = 0.0;
};

struct solution_Ant_team
{
	solution_Ant ant_team[CarCount+1];//蚂蚁团队数量（车辆数量）
	double tour_time[CityCount];//每个点对应的完成时间
	double tour_punish[CityCount];
	double ant_team_totallen=0.0;
	double total_delay = 0.0;
	double TC = 0.0;
};