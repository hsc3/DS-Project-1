#pragma once
#include "UserListNode.h"
#include "AccountQueueNode.h"
#include <fstream>
using namespace std;

class UserList
{
private:
	UserListNode* Root;

public:
	UserList();
	~UserList();

	UserListNode* GetRoot();
	AccountBSTNode* Insert(AccountQueueNode* node);
	bool Search(char* name);
	bool Delete_Account(char* name, char* id);
	void Print_L(UserListNode* node);
	char* FindIdUser(char* id);
};
