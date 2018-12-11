#include "priority.h"

//构造函数 
Priority_Queue::Priority_Queue() :length(0)
{
	//cout << "构造函数，创建一个节点" << endl;
	this->front = this->rear = new QueueNode();
}

//析构函数 
Priority_Queue::~Priority_Queue()
{
	//cout << "析构函数" << endl;
	QueueNode *dnode = this->front;
	QueueNode *tmp = this->front;
	while (tmp != nullptr)
	{
		tmp = tmp->next;
		delete dnode;
		dnode = tmp;
	}

}

//添加节点 
bool Priority_Queue::Push(const Student &d, int p)
{
	QueueNode *add = new QueueNode(d, p, nullptr);//将要插入的节点 
	if (add == nullptr)
		return false;
	//要根据优先级构造队列，数字越小优先级越高应该， 数字最小的应该放在最前面 
	if (this->front == this->rear)
	{
		//cout << "该队列为空，直接将节点插入即可" << endl;
		this->rear->next = add;
		this->rear = add;
		this->length++;
		return true;
	}
	QueueNode *move = new QueueNode();
		move=this->front->next;//移动指针找到第一个比塔优先级小的节点 
		while (move->priority > add->priority && move != nullptr) {		//原先是“<”
			move = move->next;
			if (move == nullptr)//说明队列中的优先级都比add大，直接将节点插在队尾即可 
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

//出队
bool Priority_Queue::Pop()
{
	if (this->length == 0)
	{
		cout << "队列为空，无法输出" << endl;
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

//获得队首
Student Priority_Queue::GetHead()
{
	Student TEMP;
	if (this->length == 0)
	{
		cout << "队列为空，无法获得第一个元素的值" << endl;
		return TEMP;
	}
	return this->front->next->data;
}

//输出
void Priority_Queue::ShowQueue() const
{
	if (this->length == 0)
	{
		cout << "队列为空，无法输出" << endl;
		return;
	}
	QueueNode *move = this->front->next;
	int i = 0;
	while (move != nullptr)
	{
		cout << "第" << i + 1 << "个元素输出: " << endl
			<< "data : " << move->data.getCandidateNum() << endl
			<< "priority : " << move->priority << endl;
		move = move->next;
		i++;
	}
}