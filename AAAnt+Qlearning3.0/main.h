#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <ctime>
using namespace std;
#define CityCount   26
#define AntCount  26//������������������
#define CarCount  3//��������
#define Max_capacity 2000.0

#define ��  1
#define ��  5
#define ��  0.5
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
	double tour_capacity;//�õ������
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
	int tour[CityCount + 1];//����������·����CityCount+1Ԫ����
	bool can_visit[CityCount];//�����Ƿ��ܹ����ʳ��е�nԪ��������
	//double tour_time[CityCount + 1];

	int tour_citycount;//���ϵ�ǰ�߹����е�����
	double tour_length;//�������ߵ�·������tour_length
	//double tour_capacity;//�õ������
	double select_probability[CityCount];//���϶Ը����е�ѡ���������
	double  ant_capacity; //����������
	double charging_ant;//��������
	double start_service_time = 0.0;
    double ant_delay = 0.0;
	double ant_order_start[CityCount] = { 0.0 };
	int ant_order_bach;

	double ant_order_maxdelay = 0.0;
};

struct solution_Ant_team
{
	solution_Ant ant_team[CarCount+1];//�����Ŷ�����������������
	double tour_time[CityCount];//ÿ�����Ӧ�����ʱ��
	double tour_punish[CityCount];
	double ant_team_totallen=0.0;
	double total_delay = 0.0;
	double TC = 0.0;
};