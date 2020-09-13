#pragma once

#include <vector>
#include "DataBase.h"
#include <iostream>

bool isCorrectString(string str);
vector<string>* ParseFile(string filename);
vector<string>* ParseString(string str);
bool isCorrect(string str, int type);
int StringToInt(string str); // conversation string to integer
bool isDay(string str);
bool isMonth(string str);
bool isYear(string str);
