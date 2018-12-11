#pragma
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "student.h"
#include <iostream>

class QueueNode{
public:
	Student data;//���� 
	int priority;//���ȼ� 
	QueueNode *next;
	QueueNode() :data(Student()), priority(0), next(nullptr) {}
	QueueNode(Student d, int p, QueueNode *n = nullptr) :data(d), priority(p), next(n) {}
};
//���ȶ����� 
class Priority_Queue{
private:
	QueueNode *front;//��ͷָ�� 
	QueueNode *rear;//��βָ�� 
	int length;//���г��� 
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
