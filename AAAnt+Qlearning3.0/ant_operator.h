#pragma once
#include"main.h"

void Ant_Initial(solution_Ant* Ant_temp);//蚂蚁的构造函数


void Ant_Clear(solution_Ant* Ant_temp);

void Ant_Addcity(solution_Ant* Ant_temp, int city);


void Ant_GetFirstCity(solution_Ant* Ant_temp);


void Ant_Next_City(solution_Ant* Ant_temp, double τ[CityCount][CityCount], double Deltτ[CityCount][CityCount], double alldisarray[CityCount][CityCount]);


void Ant_Build_Trip(solution_Ant* Ant_temp, double τ[CityCount][CityCount], double Deltτ[CityCount][CityCount], double alldisarray[CityCount][CityCount]);


void Ant_UpdateTourLength(solution_Ant* Ant_temp, double alldisarray[CityCount][CityCount]);//更新旅行路径长度的函数
