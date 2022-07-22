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
	UserListNode* pNext; // 링크드리스트의 다음노드를 가리키는 포인터
	AccountBSTNode* pHead; // BST에 위치한 해당 사용자의 노드를 가리키는 포인터

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
