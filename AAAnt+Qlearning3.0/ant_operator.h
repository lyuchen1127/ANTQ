#pragma once
#include"main.h"

void Ant_Initial(solution_Ant* Ant_temp);//���ϵĹ��캯��


void Ant_Clear(solution_Ant* Ant_temp);

void Ant_Addcity(solution_Ant* Ant_temp, int city);


void Ant_GetFirstCity(solution_Ant* Ant_temp);


void Ant_Next_City(solution_Ant* Ant_temp, double ��[CityCount][CityCount], double Delt��[CityCount][CityCount], double alldisarray[CityCount][CityCount]);


void Ant_Build_Trip(solution_Ant* Ant_temp, double ��[CityCount][CityCount], double Delt��[CityCount][CityCount], double alldisarray[CityCount][CityCount]);


void Ant_UpdateTourLength(solution_Ant* Ant_temp, double alldisarray[CityCount][CityCount]);//��������·�����ȵĺ���
