#include <iostream>
#include <string>
#include "student.h"
using namespace std;


Student::Student(){
		CandidateNum = 0;
		CandiName = "zhangsan";
		int i = 0, j = 0;
		for (i = 0; i < 5; i++) {						//Score
			Score[i] = 0;
		}
		for (i = 0; i < 6; i++) {						//Aspiration
			for (j = 0; j < 6; j++) {
				Aspiration[i][j] = 0;
			}
		}
		isReassign = true;
		isRelegated = false;
		Universitynum = 0;
		Universityname = ' ';
		Majornum = 0;
		Majorname = ' ';
		countatMajor = 0;
		countatAspira = 0;
		totalSub = 0;
}
	
Student::Student(int cnum, string cname, int score[5], int aspiration[6][6], bool isreassign) {
		CandidateNum = cnum;							//CandidateNum
		CandiName = cname;								//CandiName
		int i = 0, j = 0;
		for (i = 0; i < 5; i++) {						//Score
			Score[i] = score[i];
		}
		for (i = 0; i < 6; i++) {						//Aspiration
			for (j = 0; j < 6; j++) {
				Aspiration[i][j] = aspiration[i][j];
			}
		}
		isReassign = isreassign;		//isReassign
		isRelegated = false;
		Universitynum = 0;
		Universityname = ' ';
		Majornum = 0;
		Majorname = ' ';
		countatMajor = 0;
		countatAspira = 0;
		totalSub = 0;
}

void Student::copyStudent(Student stu) {
	CandidateNum = stu.getCandidateNum();					//CandidateNum
	CandiName = stu.getCandiName();								//CandiName
	int i = 0, j = 0;
	for (i = 0; i < 5; i++) {						//Score
		Score[i] = stu.getScore(i+1);
	}
	for (i = 0; i < 6; i++) {						//Aspiration
		for (j = 0; j < 6; j++) {
			Aspiration[i][j] = stu.getspecificMajor(i, j);
		}
	}
	isReassign = stu.getisReassign();		//isReassign
	isRelegated = stu.getRelegated();
	Universitynum = stu.getUniversitynum();
	Universityname = stu.getUniversityname();
	Majornum = stu.getMajornum();
	Majorname = stu.getMajorname();
	countatMajor = stu.getCountatMajor();
}

void Student::setCandidateNum(int num) {
	CandidateNum = num;
}

void Student::setCandiName(string name) {
	CandiName = name;
}

void Student::setScore(int iteration, int score) {
	Score[iteration - 2] = score;
}

void Student::setCandiScore(int score) {
	Score[0] = score;
}

void Student::setAspiration(int iteration, int aspir) {
	int temp = 0;
	int tempaspirnum = 0;
	temp = (iteration - 7) % 6;
	tempaspirnum = (iteration - 7) / 6;
	
	Aspiration[tempaspirnum][temp] = aspir;
}

void Student::setisReassign(int i){
	if (i == 1) { isReassign = true; }
	else { isReassign = false; }
}

void Student::setRelegated() {
	isRelegated = true;
}

void Student::setUniversityNum(int universitynum) {
	Universitynum = universitynum;
}

int Student::getUniversityNum() {
	return Universitynum;
}

void Student::setUniversity(int universitynum, string universityname, int majornumber, string majorname) {
	Universitynum = universitynum;
	Universityname = universityname;
	Majornum = majornumber;
	Majorname = majorname;
}

int Student::getCandidateNum() {
	return CandidateNum;
}

string Student::getCandiName() {
	return CandiName;
}

int Student::getScore(int i) {
	int backscore = 0;
	switch (i)
	{
	case 1:backscore = Score[0]; break;		//total score
	case 2:backscore = Score[1]; break;		//chinese
	case 3:backscore = Score[2]; break;		//math
	case 4:backscore = Score[3]; break;		//english
	case 5:backscore = Score[4]; break;		//integration
 	default:backscore = 0;
		break;
	}
	return backscore;
}

int Student::getAspirationschool(int aspirationnum) {
	return Aspiration[aspirationnum][0];
}

int Student::getspecificMajor(int aspirationnum, int majornumber) {
	return Aspiration[aspirationnum][majornumber];
}

int * Student::getAspiration(int i) {
	int backaspiration[6];
	int j = 0;
	switch (i)
	{
	case 1:											//NO.1 aspiration
		for (j = 0; j < 6; j++) {
			backaspiration[j] = Aspiration[0][j];
		}
		break;
	case 2:											//NO.2 aspiration
		for (j = 0; j < 6; j++) {
			backaspiration[j] = Aspiration[1][j];
		}
		break;
	case 3:											//NO.3 aspiration
		for (j = 0; j < 6; j++) {
			backaspiration[j] = Aspiration[2][j];
		}
		break;
	case 4:											//NO.4 aspiration
		for (j = 0; j < 6; j++) {
			backaspiration[j] = Aspiration[3][j];
		}
		break;
	case 5:											//NO.5 aspiration
		for (j = 0; j < 6; j++) {
			backaspiration[j] = Aspiration[4][j];
		}
		break;
	case 6:											//NO.6 aspiration
		for (j = 0; j < 6; j++) {
			backaspiration[j] = Aspiration[5][j];
		}
		break;
	default:
		break;
	}
	return backaspiration;
}

bool Student::getisReassign() {
	return isReassign;
}

bool Student::getRelegated() {
	return isRelegated;
}

int Student::getUniversitynum() {
	return Universitynum;
}

string Student::getUniversityname() {
	return Universityname;
}

int Student::getMajornum() {
	return Majornum;
}

string Student::getMajorname() {
	return Majorname;
}

void Student::setCountatMajor() {
	countatMajor++;
}

int Student::getCountatMajor() {
	return countatMajor;
}

void Student::setCountatAspira(int aspira) {
	countatAspira = aspira;
}

int Student::getCountatAspira() {
	return countatAspira;
}

void Student::increaseSub(int subnum) {
	totalSub += subnum;
}

int Student::getTotalSub() {
	return totalSub;
}