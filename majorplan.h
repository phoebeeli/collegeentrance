#pragma once
#ifndef MAJORPLAN_H
#define MAJORPLAN_H

#include <string>
using namespace std;

class MajorPlan {
private:
	int MajorNum;
	string MajorName;
	int MajorPlannum;
	int MajorActualnum;
public:
	MajorPlan();
	MajorPlan(int majornum, string majorname, int majorplannum, int majoractualnum);
	void increaseActualnum();
	void setMajorNum(int majornum);
	void setMajorName(string majorname);
	void setMajorPlannum(int majorplannum);
	void setMajorActualnum(int majoractualnum);
	int getMajornum();
	string getMajorname();
	int getMajorPlannum();
	int getMajorAcutualnum();
};

#endif // !MAJORPLAN_H

