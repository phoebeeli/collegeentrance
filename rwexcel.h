#pragma once
#ifndef FILE_H
#define FILE_H

#include "student.h"
#include "university.h"

class File {
public:
	bool WriteStudentFile();
	bool WriteUniversityFile();
	bool WriteFinishedStudentFile(Student *student[], int totalnum);
	bool ReadStudentFile(Student *student[], int totalnum);
	bool ReadUniversityFile(University *university[], int schoolnum);
};

#endif // !FILE_H

