#pragma once
#include <string>
#include "WorkRecord.h"
using namespace std;


int inputInt(const string& prompt, int minValue, int maxValue);
float inputFloat(const string& prompt, float minValue, float maxValue);
string inputString(const string& prompt, int maxLength);
bool inputYesNo(const string& prompt);
void inputDate(const string& prompt, int& day, int& month, int& year);


string inputFullName();
string inputPosition();
string inputDepartment();
float inputHours();


WorkRecord inputRecord();