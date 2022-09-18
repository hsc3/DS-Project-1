#include "AccountQueue.h"

AccountQueue::AccountQueue()
{
	queue_size = 0;
	Front = NULL;
}

AccountQueue::~AccountQueue()
{
	delete Front;
	Front = NULL;
}

AccountQueueNode* AccountQueue::POP()
{
	AccountQueueNode* popNode = this->Front;

	this->Front = popNode->GetNext();
	this->queue_size--;
	return popNode;
}

bool AccountQueue::PUSH(AccountQueueNode* node)
{
	if (this->EMPTY()) // 첫 노드의 삽입인 경우
	{
		this->Front = node;
	}

	else // 첫 노드의 삽입이 아닌 경우 -> 큐의 마지막노드를 찾아간다
	{
		AccountQueueNode* pushQueueNode = this->Front;
		while (pushQueueNode->GetNext() != NULL)
		{
			pushQueueNode = pushQueueNode->GetNext();
		}
		pushQueueNode->SetNext(node);
	}

	this->queue_size++;
	return true;
}

bool AccountQueue::EMPTY()
{
	if (queue_size == 0) return true;
	else return false;
}

int AccountQueue::SIZE()
{
	return queue_size;
}

void AccountQueue::PRINT()
{
	ofstream flog;
	flog.open("log.txt", ios::app);
	AccountQueueNode* printQueueNode = this->Front;
	
	while(printQueueNode != NULL)
	{
		flog << printQueueNode->GetName() << "/" << printQueueNode->GetAge() << "/" << printQueueNode->GetId() << endl;
		printQueueNode = printQueueNode->GetNext();
	}

	flog.close();
	return;
}