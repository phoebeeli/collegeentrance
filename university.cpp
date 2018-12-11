#include <iostream>
#include <string>
#include "majorplan.h"
#include "university.h"
using namespace std;

#define majornum 6

University::University() {
	UniversityNum = 0;
	UniversityName = "NULL";
	Plannum = 5;
	Actualnum = 0;
	//int i = 0;
	for (int i = 0; i < majornum; i++) {						//Major
		Major[i] = new MajorPlan();
	}
	testRange = 0;
	for (int i = 0; i < 5; i++) {
		Range[i] = 0;
	}
	unistu = new Priority_Queue();
}

University::University(int universitynum, string universityname, int plannum, int actualnum, MajorPlan major[majornum], int testrange, int range1, int range2, int range3, int range4, int range5) {
	UniversityNum = universitynum;
	UniversityName = universityname;
	Plannum = plannum;
	Actualnum = actualnum;
	int i = 0;
	for (i = 0; i < majornum; i++) {						//Major
		Major[i] = new MajorPlan();
	}
	testRange = testRange;
	Range[0] = range1;
	Range[1] = range2;
	Range[2] = range3;
	Range[3] = range4;
	Range[4] = range5;
	unistu = new Priority_Queue();
}

void University::increaseActualnum() {
	Actualnum = Actualnum + 1;
}

void University::decreaseActualnum() {
	Actualnum = Actualnum - 1;
}

void University::increaseMajorActualnum(int majornumber) {
	Major[majornumber-1]->increaseActualnum();
}

void University::setUniversityNum(int universnum) {
	UniversityNum = universnum;
}

void University::setUniversityName(string universname) {
	UniversityName = universname;
}

void University::setUniversityPlannum(int plannum) {
	Plannum = plannum;
}

void University::setUniversityActualnum(int actualnum) {
	Actualnum = actualnum;
}

void University::setUniversityMajorTotalnum(int totalnum) {
	majortotalnum = totalnum;
}

void University::setMajorNum(int majornumber, int majornumm) {
	Major[majornumber]->setMajorNum(majornumm);
}

void University::setMajorName(int majornumber, string majorname) {
	Major[majornumber]->setMajorName(majorname);
}

void University::setMajorPlannum(int majornumber, int majorplannum) {
	Major[majornumber]->setMajorPlannum(majorplannum);
}

void University::setMajorActualnum(int majornumber, int majoractualnum) {
	Major[majornumber]->setMajorActualnum(majoractualnum);
}

int University::getMajornum() {
	return majornum;
}

int University::getUniversitynum() {
	return UniversityNum;
}

string University::getUniversityname() {
	return UniversityName;
}

MajorPlan* University::getUniversitymajor(int num) {
	return Major[num-1];
}

bool University::isFull() {
	if (Plannum > Actualnum) { return false; }
	else { return true; }
}

bool University::isMajorFull(int majornumber) {
	if ((Major[majornumber-1]->getMajorPlannum()) > (Major[majornumber-1]->getMajorAcutualnum())) {
		return false; 
	}
	else { return true; }
}

bool University::isRange() {
	if (testRange == 0) { return false; }
	else { return true; }
}

void University::settestRange(int testrange) {
	testRange = testrange;
}

void University::setspecificRange(int specificrange, int num) {
	Range[num] = specificrange;
}

int University::getspecificRange(int num) {
	return Range[num];
}

void University::setPriorityStu(Student stu) {
	unistu->Push(stu,stu.getScore(1));
}

Priority_Queue* University::getPriorityQueue() {
	return unistu;
}