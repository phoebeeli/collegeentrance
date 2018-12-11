#pragma once
#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include "majorplan.h"
#include "priority.h"
#include <string>

#define majornum 6

class University {
private:
	int UniversityNum;
	string UniversityName;
	int Plannum;
	int Actualnum;
	int majortotalnum;
	MajorPlan *Major[majornum];
	int testRange;
	int Range[5];
	Priority_Queue *unistu;
public:
	University();
	University(int universitynum, string universityname, int plannum, int actualnum, MajorPlan major[majornum], int testrange,int range1,int range2,int range3, int range4, int range5);
	void increaseActualnum();
	void decreaseActualnum();
	void increaseMajorActualnum(int majornumber);
	void setUniversityNum(int universnum);
	void setUniversityName(string universname);
	void setUniversityPlannum(int plannum);
	void setUniversityActualnum(int actualnum);
	void setUniversityMajorTotalnum(int totalnum);
	void setMajorNum(int majornumber, int majornumm);
	void setMajorName(int majornumber, string majorname);
	void setMajorPlannum(int majornumber, int majorplannum);
	void setMajorActualnum(int majornumber, int majoractualnum);
	int getMajornum();
	int getUniversitynum();
	string getUniversityname();
	MajorPlan* getUniversitymajor(int num);
	bool isFull();
	bool isMajorFull(int majornumber);
	bool isRange();
	void settestRange(int testrange);
	void setspecificRange(int specificrange, int num);
	int getspecificRange(int num);
	void setPriorityStu(Student stu);
	Priority_Queue * getPriorityQueue();
};

#endif // !UNIVERSITY_H
