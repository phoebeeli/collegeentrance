//#include "stdafx.h"
#include <fstream> 
#include <string>
#include <iostream>
#include <sstream>
#include <streambuf> 
#include <vector>
#include "rwexcel.h"
using namespace std;

bool File::WriteStudentFile(){
	ofstream oFile;

	//打开要输出的文件 
	oFile.open("scorefile.csv", ios::out | ios::trunc);    // 这样就很容易的输出一个需要的excel 文件
	oFile << "studentnum" << "," << "studentname" << "," << "scoretotal" << "," << "scorechinese" << "," << "scoremath" << "," << "scoreenglish" << "," << "scorecomprehensive" << "," << "teacher" << endl;
	oFile << "001" << "," << "yuan" << "," << "740" << "," << "150" << "," << "150" << "," << "150" << "," << "290" << "," << "Jim" << endl;
	oFile << "001" << "," << "kai" << "," << "740" << "," << "140" << "," << "150" << "," << "150" << "," << "300" << "," << "Jim" << endl;

	oFile.close();
	//getchar();
	return true;
}

bool File::WriteUniversityFile() {
	ofstream oFile;

	//打开要输出的文件 
	oFile.open("universitydatafile.csv", ios::out | ios::trunc);    // 这样就很容易的输出一个需要的excel 文件
	oFile << "universitynum" << "," << "universityname" << "," << "universityplannum" << "," << "universityactualnum" << "," << "majortotalnum" << "," << "majornum" << "," << "majorname" << "," << "majorplannum" << "," << "majoractualnum" << endl;
	oFile << "001" << "," << "bjut" << "," << "2" << "," << "0" << "," << "1" << "," << "1" << "," << "cs" << "," << "2" << "," << "0" << endl;
	//oFile << "001" << "," << "kai" << "," << "740" << "," << "140" << "," << "150" << "," << "150" << "," << "300" << "," << "Jim" << endl;

	
	oFile.close();
	//getchar();
	return true;
}

bool File::WriteFinishedStudentFile(Student *student[], int totalnum) {
	ofstream oFile;

	oFile.open("finishedstudent.csv", ios::out | ios::trunc);
	oFile << "studentnum" << "," << "studentname" << "," << "scoretotal" << "," << "scorechinese" << "," << "scoremath" << "," << "scoreenglish" << "," << "scorecomprehensive" << "," << "isRelegated" << "," << "universitynum" << "," << "universityname" << "," << "majornum" << "," << "majorname" << endl;
	for (int i = 0; i < totalnum; i++) {
		oFile << student[i]->getCandidateNum() << "," << student[i]->getCandiName() << ",";
		for (int j = 1; j < 6; j++) {
			oFile << student[i]->getScore(j) << ",";
		}
		oFile << student[i]->getRelegated() << "," << student[i]->getUniversitynum() << "," << student[i]->getUniversityname() << "," << student[i]->getMajornum() << "," << student[i]->getMajorname() << endl;
	}

	return true;
}

bool File::ReadStudentFile(Student *student[], int totalnum)
{
	//打开要输出的文件 
	ifstream iFile("scorefile.csv",ios::in);

	string lineStr;
	stringstream ss;
	int tempint = 0;
	int line = 0;
	int i = 0;
	int iteration = 0;

	while (getline(iFile, lineStr)) {
		//打印整行
		//cout << lineStr << endl;
		if (line == 0) {
			line++;
			continue;
		}
		stringstream str(lineStr);
		string temp;
		while ((getline(str, temp, ','))&&(i!=totalnum)) {
			if (iteration == 0) {
				ss << temp;
				ss >> tempint;
				student[i]->setCandidateNum(tempint);
				iteration = 1;
				ss.clear();
				ss.str("");
				continue;
			}
			else if(iteration==1){
				student[i]->setCandiName(temp);
				iteration = 2;
				continue;
			}
			else if ((iteration >= 2) && (iteration <= 6)) {
				ss << temp;
				ss >> tempint;
				student[i]->setScore(iteration, tempint);
				ss.clear();
				ss.str("");
				iteration++;
				continue;
			}
			else if ((iteration >= 7) && (iteration <= 42)) {
				ss << temp;
				ss >> tempint;
				student[i]->setAspiration(iteration, tempint);
				ss.clear();
				ss.str("");
				iteration++;
				continue;
			}
			else if (iteration == 43) {
				ss << temp;
				ss >> tempint;
				student[i]->setisReassign(tempint);
				ss.clear();
				ss.str("");
				iteration = 0;
				continue;
			}	
		}
		i++;
	}

	//getchar();
	return true;
}

bool File::ReadUniversityFile(University *university[], int schoolnum) {
	//打开要输出的文件 
	ifstream iFile("universitydatafile.csv", ios::in);

	string lineStr;
	stringstream ss;
	int tempint = 0;
	int line = 0;
	int i = 0;
	int iteration = 0;
	int majornumber = 0;
	int majortotalnum = 0;

	while (getline(iFile, lineStr)) {
		//打印整行
		//cout << lineStr << endl;
		if (line == 0) {
			line++;
			continue;
		}
		stringstream str(lineStr);
		string temp;
		iteration = 0;
		majornumber = 0;
		while ((getline(str, temp, ',')) && (i != schoolnum)) {
			if (iteration == 0) {
				ss << temp;
				ss >> tempint;
				university[i]->setUniversityNum(tempint);
				iteration = 1;
				ss.clear();
				ss.str("");
				continue;
			}
			else if (iteration == 1) {
				university[i]->setUniversityName(temp);
				iteration = 2;
				continue;
			}
			else if (iteration == 2) {
				ss << temp;
				ss >> tempint;
				university[i]->settestRange(tempint);
				ss.clear();
				ss.str("");
				iteration++;
				continue;
			}
			else if (iteration == 3 || iteration == 4 || iteration == 5 || iteration == 6 || iteration == 7) {
				ss << temp;
				ss >> tempint;
				university[i]->setspecificRange(tempint, iteration - 3);
				ss.clear();
				ss.str("");
				iteration++;
				continue;
			}
			else if (iteration == 8) {
				ss << temp;
				ss >> tempint;
				university[i]->setUniversityPlannum(tempint);
				ss.clear();
				ss.str("");
				iteration++;
				continue;
			}
			else if (iteration == 9) {
				ss << temp;
				ss >> tempint;
				university[i]->setUniversityActualnum(tempint);
				ss.clear();
				ss.str("");
				iteration++;
				continue;
			}
			else if (iteration == 10) {
				ss << temp;
				ss >> tempint;
				university[i]->setUniversityMajorTotalnum(tempint);
				majortotalnum = tempint;
				ss.clear();
				ss.str("");
				iteration++;
				continue;
			}
			else if (((iteration - 11) % 4) == 0) {
				ss << temp;
				ss >> tempint;
				university[i]->setMajorNum(majornumber, tempint);
				ss.clear();
				ss.str("");
				iteration++;
				majortotalnum--;
				continue;
			}
			else if (((iteration - 11) % 4) == 1) {
				university[i]->setMajorName(majornumber, temp);
				iteration++;
				continue;
			}
			else if (((iteration - 11) % 4) == 2) {
				ss << temp;
				ss >> tempint;
				university[i]->setMajorPlannum(majornumber, tempint);
				ss.clear();
				ss.str("");
				iteration++;
				continue;
			}
			else if (((iteration - 11) % 4) == 3) {
				ss << temp;
				ss >> tempint;
				university[i]->setMajorActualnum(majornumber, tempint);
				ss.clear();
				ss.str("");
				iteration++;
				majornumber++;
				if (majortotalnum == 0) { break; }
				continue;
			}
		}
		i++;
	}

	//getchar();
	return true;
}

