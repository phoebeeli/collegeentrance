#pragma once
#ifndef STUDENT_H
#define STHDENT_H

#include <string>
using namespace std;

class Student {
private:
	int CandidateNum;
	string CandiName;
	int Score[5];
	int Aspiration[6][6];
	bool isReassign;
	bool isRelegated;
	int Universitynum;
	string Universityname;
	int Majornum;
	string Majorname;
	int countatMajor;
	int countatAspira;
	int totalSub;
public:
	Student();
	Student(int cnum, string cname, int score[5], int aspiration[6][6], bool isreassign);
	void copyStudent(Student stu);
	void setCandidateNum(int num);
	void setCandiName(string name);
	void setScore(int i, int score);
	void setAspiration(int i, int aspir);
	void setisReassign(int i);
	void setRelegated();
	void setUniversityNum(int universitynum);
	void setUniversity(int universitynum, string universityname, int majornumber, string majorname);
	int getCandidateNum();
	string getCandiName();
	int getScore(int i);
	int getAspirationschool(int aspirationnum);
	int getspecificMajor(int aspirationnum, int majornumber);
	int *getAspiration(int i);
	bool getisReassign();
	bool getRelegated();
	int getUniversitynum();
	string getUniversityname();
	int getMajornum();
	string getMajorname();
	void setCountatMajor();
	int getCountatMajor();
	int getUniversityNum();
	void setCountatAspira(int aspira);
	int getCountatAspira();
	void setCandiScore(int score);
	void increaseSub(int subnum);
	int getTotalSub();
};

#endif // !STUDENT_H
