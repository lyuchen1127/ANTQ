#pragma once
#include"main.h"
double calculateTwoDistance(read_city RC[CityCount], int i, int j);

double calculateSumOfDistance(solution_Ant ant_temp, double alldisarray[CityCount][CityCount]);

void calculatetimewindow(solution_Ant_team* ant_temp, double alldisarray[CityCount][CityCount], read_city RC[CityCount]);

void calculatetimepuinish(solution_Ant_team* ant_temp, double alldisarray[CityCount][CityCount], read_city RC[CityCount], read_order OC);