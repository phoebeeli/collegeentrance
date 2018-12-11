#pragma once

#ifndef SYSTEMTEST_H
#define SYSTEMTEST_H

#include "student.h"
#include "university.h"

extern Student *finishedstudent[];

int AcceptDistribution(Student *student, University *university);		//·þ´Ó·ÖÅä
void OutputScreen(Student *student[], University *university[]);
int maintime();
void searchSpecificUniStu(int universitynum, Student *student[], int totalstunum);

#endif // !SYSTEMTEST_H

