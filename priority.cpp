#include "priority.h"

//���캯�� 
Priority_Queue::Priority_Queue() :length(0)
{
	//cout << "���캯��������һ���ڵ�" << endl;
	this->front = this->rear = new QueueNode();
}

//�������� 
Priority_Queue::~Priority_Queue()
{
	//cout << "��������" << endl;
	QueueNode *dnode = this->front;
	QueueNode *tmp = this->front;
	while (tmp != nullptr)
	{
		tmp = tmp->next;
		delete dnode;
		dnode = tmp;
	}

}

//��ӽڵ� 
bool Priority_Queue::Push(const Student &d, int p)
{
	QueueNode *add = new QueueNode(d, p, nullptr);//��Ҫ����Ľڵ� 
	if (add == nullptr)
		return false;
	//Ҫ�������ȼ�������У�����ԽС���ȼ�Խ��Ӧ�ã� ������С��Ӧ�÷�����ǰ�� 
	if (this->front == this->rear)
	{
		//cout << "�ö���Ϊ�գ�ֱ�ӽ��ڵ���뼴��" << endl;
		this->rear->next = add;
		this->rear = add;
		this->length++;
		return true;
	}
	QueueNode *move = new QueueNode();
		move=this->front->next;//�ƶ�ָ���ҵ���һ���������ȼ�С�Ľڵ� 
		while (move->priority > add->priority && move != nullptr) {		//ԭ���ǡ�<��
			move = move->next;
			if (move == nullptr)//˵�������е����ȼ�����add��ֱ�ӽ��ڵ���ڶ�β���� 
			{
				this->rear->next = add;
				this->rear = add;
				this->length++;
				return true;
			}
		}
	QueueNode *tmp = this->front;
	while (tmp->next != move)
		tmp = tmp->next;
	add->next = move;
	tmp->next = add;
	this->length++;
	return true;
}

//����
bool Priority_Queue::Pop()
{
	if (this->length == 0)
	{
		cout << "����Ϊ�գ��޷����" << endl;
		return false;
	}
	QueueNode *dnode = this->front->next;
	this->front->next = dnode->next;
	if (this->length == 1)
		this->rear = this->front;
	delete dnode;
	this->length--;
	return true;
}

//��ö���
Student Priority_Queue::GetHead()
{
	Student TEMP;
	if (this->length == 0)
	{
		cout << "����Ϊ�գ��޷���õ�һ��Ԫ�ص�ֵ" << endl;
		return TEMP;
	}
	return this->front->next->data;
}

//���
void Priority_Queue::ShowQueue() const
{
	if (this->length == 0)
	{
		cout << "����Ϊ�գ��޷����" << endl;
		return;
	}
	QueueNode *move = this->front->next;
	int i = 0;
	while (move != nullptr)
	{
		cout << "��" << i + 1 << "��Ԫ�����: " << endl
			<< "data : " << move->data.getCandidateNum() << endl
			<< "priority : " << move->priority << endl;
		move = move->next;
		i++;
	}
}