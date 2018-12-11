#include <iostream>
#include <string>
#include "majorplan.h"
using namespace std;


MajorPlan::MajorPlan() {
	MajorNum = 0;
	MajorName = " ";
	MajorPlannum = 0;
	MajorActualnum = 0;
}
MajorPlan::MajorPlan(int majornum, string majorname, int majorplannum, int majoractualnum) {
	MajorNum = majornum;
	MajorName = majorname;
	MajorPlannum = majorplannum;
	MajorActualnum = majoractualnum;
}

void MajorPlan::increaseActualnum() {
	MajorActualnum = MajorActualnum + 1;
}

void MajorPlan::setMajorNum(int majornum) {
	MajorNum = majornum;
}

void MajorPlan::setMajorName(string majorname) {
	MajorName = majorname;
}

void MajorPlan::setMajorPlannum(int majorplannum) {
	MajorPlannum = majorplannum;
}

void MajorPlan::setMajorActualnum(int amjoractualnum) {
	MajorActualnum = amjoractualnum;
}

int MajorPlan::getMajornum() { return MajorNum; }

string MajorPlan::getMajorname() { return MajorName; }

int MajorPlan::getMajorPlannum() { return MajorPlannum; }

int MajorPlan::getMajorAcutualnum() { return MajorActualnum; }
