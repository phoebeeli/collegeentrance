#include <iostream>
#include "queue.h"

lnkNode::lnkNode(Student student, lnkNode *next) {
	stu = student;
	lnext = next;
}

lnkQueue::lnkQueue(int size) {
	size = 0;
	front = rear = NULL;
}

lnkQueue::~lnkQueue() {
	clear();
}

void lnkQueue::clear() {
	while (front != NULL) { 
		rear = front;
		front = front->lnext;
		delete rear;
	}
	rear = NULL;
	size = 0;
}

bool lnkQueue::isEmpty() {
	if (front == NULL) { return true; }
	else { return false; }
}

bool lnkQueue::enQueue(const Student item) {
	if (rear == NULL) {
		front = rear = new lnkNode(item, NULL);
	}
	else {
		rear->lnext = new lnkNode(item, NULL);
		rear = rear->lnext;
	}
	size++;
	return true;
}

bool lnkQueue::deQueue(Student& item) {
	lnkNode *tmp;
	if (size == -1) {
		cout << "The queue is empty." << endl;
		return false;
	}
	item = front->stu;		//Ô­ÏÈÊÇ&item, £¿£¿£¿
	tmp = front;
	front = front->lnext;
	delete tmp;
	if (front == NULL) { rear = NULL; }
	size--;
	return true;
}

bool lnkQueue::getFront(Student &item) {
	if (size == 0) {
		cout << "The queue is empty." << endl;
		return false;
	}
	item = front->stu;
	return true;
}
