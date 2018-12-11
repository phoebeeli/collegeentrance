#pragma
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "student.h"
#include <iostream>

class QueueNode{
public:
	Student data;//数据 
	int priority;//优先级 
	QueueNode *next;
	QueueNode() :data(Student()), priority(0), next(nullptr) {}
	QueueNode(Student d, int p, QueueNode *n = nullptr) :data(d), priority(p), next(n) {}
};
//优先队列类 
class Priority_Queue{
private:
	QueueNode *front;//队头指针 
	QueueNode *rear;//队尾指针 
	int length;//队列长度 
public:
	Priority_Queue();
	~Priority_Queue();
	bool isEmpty() { return this->length == 0; }
	int size() const { return this->length; }
	bool Push(const Student &d, int p);
	bool Pop();
	Student GetHead();
	void ShowQueue() const;
};

#endif // !PRIORITYQUEUE_H
