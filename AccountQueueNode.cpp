#include "AccountQueueNode.h"

AccountQueueNode::AccountQueueNode()
{
	this->User_Name = NULL;
	this->User_Id = NULL;
	this->pNext = NULL;
}

AccountQueueNode::~AccountQueueNode()
{
	delete User_Name;
	delete User_Id;
	delete pNext;
}

char* AccountQueueNode::GetName()
{
	return this->User_Name;
}

int AccountQueueNode::GetAge()
{
	return this->User_age;
}

char* AccountQueueNode::GetId()
{
	return this->User_Id;
}
AccountQueueNode* AccountQueueNode::GetNext()
{
	return this->pNext;
}
void AccountQueueNode::SetName(char* name)
{
	this->User_Name = name;
}

void AccountQueueNode::SetAge(int age)
{
	this->User_age = age;
}

void AccountQueueNode::SetId(char* id)
{
	this->User_Id = id;
}

void AccountQueueNode::SetNext(AccountQueueNode* node)
{
	this->pNext = node;
}
