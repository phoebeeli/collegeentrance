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

int AcceptDistribution(Student *student, University *university);		//���ӷ���

int AcceptDistribution(Student *student, University *university) {
	int majornnum = university->getMajornum(); 
	int i = 1;
	for (i = 1; i < majornum+1; i++) {
		if (university->isMajorFull(i) == false) {		//���������רҵ��û��������������רҵ
			university->increaseMajorActualnum(i);		//��רҵ��ǰʵ��¼ȡ����+1
			//����ѧ��д��excel�У�����������������������������������������������������������������������������������������������
			return i;
		}
	}
	return i;
}

void getUniversDone(University *university[], int uniused[],int finishednum) {		//����
	Student *currstu = new Student();
	int majornumnow = 1;		//��ǰ�ǿ������ĵڼ�־Ը
	int currentmajornum = 0;	//��רҵ�ı��
	//int totalsub = 0;			//�ܹ�����
	//University *curruni = new University();
	for (int i = 0; i < schoolnum; i++) {
		if (uniused[i] == 0) { continue; }
		while (university[i]->getPriorityQueue()->isEmpty() != true) {
			*currstu=university[i]->getPriorityQueue()->GetHead();
			university[i]->getPriorityQueue()->Pop();
			majornumnow = currstu->getCountatMajor();
			if (majornumnow == 5) {
				if (currstu->getisReassign() == true) {			//���ӷ���
					currentmajornum=AcceptDistribution(currstu, university[i]);
					MajorPlan *truemajor = new MajorPlan();
					truemajor = university[i]->getUniversitymajor(currentmajornum);
					currstu->setUniversity(university[i]->getUniversitynum(), university[i]->getUniversityname(), truemajor->getMajornum(), truemajor->getMajorname());
					currstu->setCandiScore(currstu->getScore(1) + currstu->getTotalSub());
					finishedstudent[finishednum]->copyStudent(*currstu);
					finishednum++;
					continue;
				}
				else {//���˵�
					university[i]->decreaseActualnum();	//��ԺУ��ʵ����ѧ����-1
					currstu->setRelegated();
					currstu->setCandiScore(currstu->getScore(1) + currstu->getTotalSub());
					finishedstudent[finishednum]->copyStudent(*currstu);
					finishednum++;
				}
				continue;
			}
			currentmajornum = currstu->getspecificMajor(currstu->getCountatAspira(), majornumnow+1);
			if (university[i]->isMajorFull(currentmajornum) == false) {		//��רҵû������
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
	//����ѧ���ɼ�����_test
	Student *student[totalnum];
	for (int i = 0; i < totalnum; i++) {
		student[i] = new Student();
	}

	File *filestu = new File();
	filestu->ReadStudentFile(student, totalnum);

	//�����ѧ������Ϣ
	University *university[schoolnum];
	for (int i = 0; i < schoolnum; i++) {
		university[i] = new University();
	}

	File *fileuni = new File();
	fileuni->ReadUniversityFile(university, schoolnum);

	//����
	QuickSort(student, 0, totalnum-1);

	//���η������
	lnkQueue  students(totalnum);
	for (int i = 0; i < totalnum; i++) {
		students.enQueue(*student[i]);
	}

	//�������е�ѧ������ȡ������Ϊ���Ƿ���ѧУ��Ϣ
	Student *currentstu = new Student();
	int currentaspir[6] = { 0 };			//
	University *currentuni = new University();
	int currentmajornum = 0;
	int unirange[schoolnum] = { 0 };	//range school ���

	for (int i = 0; i < totalnum; i++) {
		finishedstudent[i] = new Student();
	}
	int finishednum = 0;

	//-------------------------------------------------------------------------------------------------------------------��ѭ��
	while (students.isEmpty() != true) {
		//students.getFront(*currentstu);
		students.deQueue(*currentstu);
		int aspirationnum = 0;	//�ڼ�־Ը n-1
		for (aspirationnum = 0; aspirationnum < 6; aspirationnum++) {		//6��ƽ��־Ը
			currentaspir[0] = currentstu->getAspirationschool(aspirationnum);			//�õ��ڣ�־Ը��Ϣ	
			for (int now = 1; now < 6; now++) {
				currentaspir[now] = currentstu->getspecificMajor(aspirationnum, now);		//�õ���־Ը����ĸ�רҵ��Ϣ
			}
			//�ҵ���ԺУ��Ϣ
			for (int school = 0; school < schoolnum; school++) {
				if (currentaspir[0] == university[school]->getUniversitynum()) {
					currentuni = university[school];
					break;
				}
			}
			//�жϸ�ԺУ�Ƿ��Ѿ�����
			if (currentuni->isFull() == true) {
				if (aspirationnum == 5) {
					currentstu->setRelegated();		//���˵�
				}
				continue;
			}
			//��û�������ѧ�������ԺУ
			currentuni->increaseActualnum();	//��ԺУ��ʵ����ѧ������1
			currentstu->setCountatAspira(aspirationnum);
			if (currentuni->isRange() == false) {			//no range
				for (int major = 1; major < 6; major++) {
					currentmajornum = currentstu->getspecificMajor(aspirationnum, major);
					if (currentuni->isMajorFull(currentmajornum) == true) {		//��רҵ�Ƿ�����
						if (major == 5) {		//5��רҵ���޷����룬���Ƿ���ӷ���
							if (currentstu->getisReassign() == true) {	//���ӷ���
								currentmajornum=AcceptDistribution(currentstu, currentuni);
							}
							else {	//���˵�
								currentuni->decreaseActualnum();	//��ԺУ��ʵ����ѧ����-1
								currentstu->setRelegated();
								//д��excel��������������������������������������������������������������������������������������
							}
						}
						continue;
					}
					//��רҵû������������רҵ
					currentuni->increaseMajorActualnum(currentmajornum);			//רҵʵ��������һ
																					//д��excel	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!��δʵ��
					break;
				}
			}
			else {					//when the university have range amang majors
				//int major = 1; 
				//currentmajornum = currentstu->getspecificMajor(aspirationnum, major);
				//����ͬѧ�ӵ���ѧУ�����ȶ�����
				unirange[currentuni->getUniversitynum()-1] = 1;		//��ѧУ�����ȶ��б�ʹ��
				//currentstu->setCandiScore(currentstu->getScore(1) - currentuni->getspecificRange(0));			//!!!!!!!!!!�ɼ�û�м���
				currentuni->setPriorityStu(*currentstu);		//�ӵ����ȶ�����
				currentstu->setCountatMajor();
				//rangepoint = 1;
				//break;
			}


			break;		//����һ������
		}

		if ( currentstu->getCountatMajor() == 0 ) {
			//���û���˵�����¼ȡ��Ϣ��¼��������Ϣ��
			if (currentstu->getRelegated() == false) {
				MajorPlan *truemajor = new MajorPlan();
				truemajor = currentuni->getUniversitymajor(currentmajornum);
				currentstu->setUniversity(currentuni->getUniversitynum(), currentuni->getUniversityname(), truemajor->getMajornum(), truemajor->getMajorname());
				finishedstudent[finishednum]->copyStudent(*currentstu);
				//currentstu = NULL;
				finishednum++;
			}
			else {		//���˵�
				finishedstudent[finishednum]->copyStudent(*currentstu);
				finishednum++;
			}
		}
	}

	//���ȶ��е���
	for (int i = 0; i < schoolnum; i++) {
		if (unirange[i] == 1) {
			//���Ⱥ���
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
