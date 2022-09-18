#include "UserListNode.h"

UserListNode::UserListNode()
{
	Name = NULL;
	Age = 0;
	AccNum = 0;
	pNext = NULL;
	pHead = NULL;
}

UserListNode::~UserListNode()
{

}

char* UserListNode::GetName()
{
	return this->Name;
}

int UserListNode::GetAge()
{
	return this->Age;
}

UserListNode* UserListNode::GetNext()
{
	return this->pNext;
}

void UserListNode::SetName(char* name)
{
	this->Name = name;
}

void UserListNode::SetAge(int age)
{
	this->Age = age;
}

void UserListNode::SetNext(UserListNode* node)
{
	this->pNext = node;
}

AccountBSTNode* UserListNode::InsertAccount(AccountBSTNode* node)
{
	if (AccNum == 0) pHead = node;

	else
	{	
		AccountBSTNode* pp = this->pHead;
		AccountBSTNode* p = this->pHead;
		while (p != NULL)
		{
			pp = p;
			p = p->GetNext();
		}
		pp->SetNext(node);
	}
	this->AccNum++;
	return node;
}

void UserListNode::Print_Accounts() // 해당 사용자가 가지고 있는 계정들을 출력
{
	ofstream flog;
	flog.open("log.txt", ios::app);
	
	AccountBSTNode* printAccountNode = this->pHead;
	while (printAccountNode != NULL)
	{
		flog << printAccountNode->GetId() << endl;
		printAccountNode = printAccountNode->GetNext();
	}
	flog.close();
	return;
}

void UserListNode::Delete_Account(char* id)
{
	AccountBSTNode* prev = this->pHead; // 삭제될 계정의 이전 계정
	AccountBSTNode* del = this->pHead; // 삭제될 계정 

	// 사용자의 해당 계정까지 이동
	while (strcmp(del->GetId(),id) != 0) 
	{
		prev = del;
		del = del->GetNext();
	}
	// 계정list에서 해당 id의 링크를 제거
	// 1) 해당 사용자의 첫번째 계정인 경우.
	if (prev == del)
	{
		this->pHead = del->GetNext();
	}
	else
	{
		prev->SetNext(del->GetNext());
	}

	this->AccNum -= 1;
	return;
}

AccountBSTNode* UserListNode::GetHead()
{
	return this->pHead;
}
