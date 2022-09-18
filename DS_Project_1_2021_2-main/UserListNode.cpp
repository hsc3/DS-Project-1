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

void UserListNode::Print_Accounts() // �ش� ����ڰ� ������ �ִ� �������� ���
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
	AccountBSTNode* prev = this->pHead; // ������ ������ ���� ����
	AccountBSTNode* del = this->pHead; // ������ ���� 

	// ������� �ش� �������� �̵�
	while (strcmp(del->GetId(),id) != 0) 
	{
		prev = del;
		del = del->GetNext();
	}
	// ����list���� �ش� id�� ��ũ�� ����
	// 1) �ش� ������� ù��° ������ ���.
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
