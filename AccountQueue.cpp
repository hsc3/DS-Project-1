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

/* Pop the first node in the Queue */
AccountQueueNode* AccountQueue::POP()
{
	AccountQueueNode* popNode = this->Front;

	this->Front = popNode->GetNext();
	this->queue_size--;
	return popNode;
}

/* Push a node int the Queue */
bool AccountQueue::PUSH(AccountQueueNode* node)
{
	if (this->EMPTY()) // insert to the front  
	{
		this->Front = node;
	}

	else // insert to the back of the queue 
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

/* return the boolean value that announce the queue is empty or not */ 
bool AccountQueue::EMPTY()
{
	if (queue_size == 0) return true;
	else return false;
}

/* return the size of the queue */
int AccountQueue::SIZE()
{
	return queue_size;
}

/* print the queue */ 
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
