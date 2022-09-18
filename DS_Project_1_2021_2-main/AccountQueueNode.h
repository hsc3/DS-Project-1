#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
class AccountQueueNode
{
private:
	char* User_Name;
	int User_age;
	char* User_Id;

	AccountQueueNode* pNext;

public:
	AccountQueueNode();
	~AccountQueueNode();

	char* GetName();
	int GetAge();
	char* GetId();
	
	AccountQueueNode* GetNext();


	void SetName(char* name);
	void SetAge(int age);
	void SetId(char* id);
	void SetNext(AccountQueueNode* node);
};