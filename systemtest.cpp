 #include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

#include "systemtest.h"
#include "majorplan.h"
#include "university.h"
#include "student.h"
#include "quicksort.h"
#include "queue.h"
#include "rwexcel.h"
//#include "priority.h"

#define totalnum 40
#define schoolnum 13

Student *finishedstudent[totalnum];

int AcceptDistribution(Student *student, University *university);		//服从分配

int AcceptDistribution(Student *student, University *university) {
	int majornnum = university->getMajornum(); 
	int i = 1;
	for (i = 1; i < majornum+1; i++) {
		if (university->isMajorFull(i) == false) {		//如果发现有专业还没有招满，则进入该专业
			university->increaseMajorActualnum(i);		//该专业当前实际录取人数+1
			//将该学生写入excel中！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
			return i;
		}
	}
	return i;
}

void getUniversDone(University *university[], int uniused[],int finishednum) {		//极差
	Student *currstu = new Student();
	int majornumnow = 1;		//当前是考生报的第几志愿
	int currentmajornum = 0;	//该专业的编号
	//int totalsub = 0;			//总共减分
	//University *curruni = new University();
	for (int i = 0; i < schoolnum; i++) {
		if (uniused[i] == 0) { continue; }
		while (university[i]->getPriorityQueue()->isEmpty() != true) {
			*currstu=university[i]->getPriorityQueue()->GetHead();
			university[i]->getPriorityQueue()->Pop();
			majornumnow = currstu->getCountatMajor();
			if (majornumnow == 5) {
				if (currstu->getisReassign() == true) {			//服从分配
					currentmajornum=AcceptDistribution(currstu, university[i]);
					MajorPlan *truemajor = new MajorPlan();
					truemajor = university[i]->getUniversitymajor(currentmajornum);
					currstu->setUniversity(university[i]->getUniversitynum(), university[i]->getUniversityname(), truemajor->getMajornum(), truemajor->getMajorname());
					currstu->setCandiScore(currstu->getScore(1) + currstu->getTotalSub());
					finishedstudent[finishednum]->copyStudent(*currstu);
					finishednum++;
					continue;
				}
				else {//被退档
					university[i]->decreaseActualnum();	//该院校的实际入学人数-1
					currstu->setRelegated();
					currstu->setCandiScore(currstu->getScore(1) + currstu->getTotalSub());
					finishedstudent[finishednum]->copyStudent(*currstu);
					finishednum++;
				}
				continue;
			}
			currentmajornum = currstu->getspecificMajor(currstu->getCountatAspira(), majornumnow+1);
			if (university[i]->isMajorFull(currentmajornum) == false) {		//该专业没有招满
				university[i]->increaseMajorActualnum(currentmajornum);
				MajorPlan *truemajor = new MajorPlan();
				truemajor = university[i]->getUniversitymajor(currentmajornum);
				currstu->setUniversity(university[i]->getUniversitynum(), university[i]->getUniversityname(), truemajor->getMajornum(), truemajor->getMajorname());
				currstu->setCandiScore(currstu->getScore(1)+currstu->getTotalSub());
				finishedstudent[finishednum]->copyStudent(*currstu);
				finishednum++;
				continue;
			}
			currstu->setCountatMajor();
			currstu->setCandiScore(currstu->getScore(1) - university[i]->getspecificRange(majornumnow-1));
			currstu->increaseSub(university[i]->getspecificRange(majornumnow - 1));
			university[i]->getPriorityQueue()->Push(*currstu, currstu->getScore(1));
		}
	}
}

void OutputScreen(Student *student[], University *university[]) {
	for (int i = 0; i < totalnum; i++) {
		cout << student[i]->getCandidateNum() << "  " << student[i]->getCandiName() << "  ";
		for (int j = 1; j < 6; j++) {
			cout << student[i]->getScore(j) << "  ";
		}
		cout << endl << "   " << student[i]->getUniversityname() << "  " << student[i]->getMajorname() << endl;
		cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
	}
}

int main() {
	//读入学生成绩数据_test
	Student *student[totalnum];
	for (int i = 0; i < totalnum; i++) {
		student[i] = new Student();
	}

	File *filestu = new File();
	filestu->ReadStudentFile(student, totalnum);

	//读入大学招生信息
	University *university[schoolnum];
	for (int i = 0; i < schoolnum; i++) {
		university[i] = new University();
	}

	File *fileuni = new File();
	fileuni->ReadUniversityFile(university, schoolnum);

	//排序
	QuickSort(student, 0, totalnum-1);

	//依次放入队列
	lnkQueue  students(totalnum);
	for (int i = 0; i < totalnum; i++) {
		students.enQueue(*student[i]);
	}

	//将队列中的学生依次取出，并为他们分配学校信息
	Student *currentstu = new Student();
	int currentaspir[6] = { 0 };			//
	University *currentuni = new University();
	int currentmajornum = 0;
	int unirange[schoolnum] = { 0 };	//range school 标记

	for (int i = 0; i < totalnum; i++) {
		finishedstudent[i] = new Student();
	}
	int finishednum = 0;

	//-------------------------------------------------------------------------------------------------------------------主循环
	while (students.isEmpty() != true) {
		//students.getFront(*currentstu);
		students.deQueue(*currentstu);
		int aspirationnum = 0;	//第几志愿 n-1
		for (aspirationnum = 0; aspirationnum < 6; aspirationnum++) {		//6个平行志愿
			currentaspir[0] = currentstu->getAspirationschool(aspirationnum);			//得到第？志愿信息	
			for (int now = 1; now < 6; now++) {
				currentaspir[now] = currentstu->getspecificMajor(aspirationnum, now);		//得到本志愿内填报的各专业信息
			}
			//找到该院校信息
			for (int school = 0; school < schoolnum; school++) {
				if (currentaspir[0] == university[school]->getUniversitynum()) {
					currentuni = university[school];
					break;
				}
			}
			//判断该院校是否已经招满
			if (currentuni->isFull() == true) {
				if (aspirationnum == 5) {
					currentstu->setRelegated();		//被退档
				}
				continue;
			}
			//若没满，则该学生进入该院校
			currentuni->increaseActualnum();	//该院校的实际入学人数＋1
			currentstu->setCountatAspira(aspirationnum);
			if (currentuni->isRange() == false) {			//no range
				for (int major = 1; major < 6; major++) {
					currentmajornum = currentstu->getspecificMajor(aspirationnum, major);
					if (currentuni->isMajorFull(currentmajornum) == true) {		//该专业是否招满
						if (major == 5) {		//5个专业均无法进入，则看是否服从分配
							if (currentstu->getisReassign() == true) {	//服从分配
								currentmajornum=AcceptDistribution(currentstu, currentuni);
							}
							else {	//被退档
								currentuni->decreaseActualnum();	//该院校的实际入学人数-1
								currentstu->setRelegated();
								//写入excel！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							}
						}
						continue;
					}
					//若专业没招满，则进入该专业
					currentuni->increaseMajorActualnum(currentmajornum);			//专业实际人数加一
																					//写入excel	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!尚未实现
					break;
				}
			}
			else {					//when the university have range amang majors
				//int major = 1; 
				//currentmajornum = currentstu->getspecificMajor(aspirationnum, major);
				//将该同学加到该学校的优先队列中
				unirange[currentuni->getUniversitynum()-1] = 1;		//该学校的优先队列被使用
				//currentstu->setCandiScore(currentstu->getScore(1) - currentuni->getspecificRange(0));			//!!!!!!!!!!成绩没有减少
				currentuni->setPriorityStu(*currentstu);		//加到优先队列中
				currentstu->setCountatMajor();
				//rangepoint = 1;
				//break;
			}


			break;		//换下一名考生
		}

		if ( currentstu->getCountatMajor() == 0 ) {
			//如果没被退档，则将录取信息记录到考生信息中
			if (currentstu->getRelegated() == false) {
				MajorPlan *truemajor = new MajorPlan();
				truemajor = currentuni->getUniversitymajor(currentmajornum);
				currentstu->setUniversity(currentuni->getUniversitynum(), currentuni->getUniversityname(), truemajor->getMajornum(), truemajor->getMajorname());
				finishedstudent[finishednum]->copyStudent(*currentstu);
				//currentstu = NULL;
				finishednum++;
			}
			else {		//被退档
				finishedstudent[finishednum]->copyStudent(*currentstu);
				finishednum++;
			}
		}
	}

	//优先队列调度
	for (int i = 0; i < schoolnum; i++) {
		if (unirange[i] == 1) {
			//调度函数
			getUniversDone(university, unirange, finishednum);
		}
	}

	QuickSort(finishedstudent, 0, totalnum-1);

	OutputScreen(finishedstudent, university);

	File *filefinished = new File();
	filefinished->WriteFinishedStudentFile(finishedstudent, totalnum);

	system("pause");
	return 0;
}

void searchSpecificUniStu(int universitynum, Student *student[], int totalstunum) {
	for (int i = 0; i < totalnum; i++) {
		if(student[i]->getUniversitynum()==universitynum){
			cout << student[i]->getCandidateNum() << " " << student[i]->getCandiName() << endl;
		}
	}
}
