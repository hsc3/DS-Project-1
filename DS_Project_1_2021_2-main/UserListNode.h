#pragma once
#include <cstring>
#include <fstream>
#include "AccountBSTNode.h"
using namespace std;

class UserListNode
{
private:
	char* Name;
	int Age;
	int AccNum;
	UserListNode* pNext; // ��ũ�帮��Ʈ�� ������带 ����Ű�� ������
	AccountBSTNode* pHead; // BST�� ��ġ�� �ش� ������� ��带 ����Ű�� ������

public:
	UserListNode();
	~UserListNode();

	char* GetName();
	int GetAge();
	int GetAccNum() {return AccNum;}
	UserListNode* GetNext();
	AccountBSTNode* GetHead();

	void SetName(char* name);
	void SetAge(int age);
	void SetNext(UserListNode* node);
	
	AccountBSTNode* InsertAccount(AccountBSTNode* node);
	void Print_Accounts();
	void Delete_Account(char* id);
};
