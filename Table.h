#pragma once
#include <iostream>
#include "WorkRecord.h"
using namespace std;


void printTableHeader(ostream& out);
void printTableRow(ostream& out, const WorkRecord& rec);
void printTableFooter(ostream& out, int count, float totalHours, float totalOvertime);

void printTableSingle(ostream& out, const WorkRecord& rec);