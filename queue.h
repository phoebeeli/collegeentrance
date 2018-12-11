#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include "student.h"
using namespace std;

class lnkNode {
public:
	Student stu;
	lnkNode *lnext;
	lnkNode(Student stu, lnkNode *next);
	lnkNode();
};

class lnkQueue{
private:
	int size;
	lnkNode *front;
	lnkNode *rear;
public:
	lnkQueue(int size);
	~lnkQueue();
	void clear();
	bool isEmpty();
	bool enQueue(const Student item);
	bool deQueue(Student& item);
	bool getFront(Student &item);
};

#endif // !QUEUE_H

