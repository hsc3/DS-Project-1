#include "AccountBSTNode.h"

AccountBSTNode::AccountBSTNode()
{
	Name = NULL;
	Id = NULL;
	pLeft = NULL;
	pRight = NULL;
	pNext = NULL;
}

AccountBSTNode::~AccountBSTNode()
{
	delete Name;
	delete Id;
	delete pLeft;
	delete pRight;
	delete pNext;
}

char* AccountBSTNode::GetName()
{
	return this->Name;
}

char* AccountBSTNode::GetId()
{
	return this->Id;
}

AccountBSTNode* AccountBSTNode::GetLeft()
{
	return this->pLeft;
}

AccountBSTNode* AccountBSTNode::GetRight()
{
	return this->pRight;
}

AccountBSTNode* AccountBSTNode::GetNext()
{
	return this->pNext;
}

void AccountBSTNode::SetName(char* name)
{
	this->Name = name;
}

void AccountBSTNode::SetId(char* disease)
{
	this->Id = disease;
}

void AccountBSTNode::SetLeft(AccountBSTNode* node)
{
	this->pLeft = node;
}

void AccountBSTNode::SetRight(AccountBSTNode* node)
{
	this->pRight = node;
}
void AccountBSTNode::SetNext(AccountBSTNode* node)
{
	this->pNext = node;
}