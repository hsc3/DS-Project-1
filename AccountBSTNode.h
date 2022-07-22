#pragma once
#include <cstring>
class AccountBSTNode
{
private:
	char* Name;
	char* Id;

	AccountBSTNode* pLeft;  // left child
	AccountBSTNode* pRight; // right child
	AccountBSTNode* pNext;  // same user's account list
	
public:
	AccountBSTNode();
	~AccountBSTNode();

	char* GetName();
	char* GetId();
	AccountBSTNode* GetLeft();
	AccountBSTNode* GetRight();
	AccountBSTNode* GetNext();


	void SetName(char* name);
	void SetId(char* id);
	void SetNext(AccountBSTNode* node);
	void SetLeft(AccountBSTNode* node);
	void SetRight(AccountBSTNode* node);
};
