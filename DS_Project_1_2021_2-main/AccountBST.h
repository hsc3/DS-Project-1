#pragma once
#include "AccountBSTNode.h"
#include "AccountQueueNode.h"
#include <fstream>
#include <queue>
using namespace std;

class AccountBST
{
private:
	AccountBSTNode* Root;

public:
	AccountBST();
	~AccountBST();

	AccountBSTNode* GetRoot();
	bool Insert(AccountBSTNode* node);       // 삽입
	bool Search_Id(char* id);                // 해당 ID 출력
	bool Delete(char* id);                   // 삭제
	void Print_PRE(AccountBSTNode* node);   // 전위출력 
	void Print_IN(AccountBSTNode* node);    // 중위출력
	void Print_POST(AccountBSTNode* node);  // 후위출력
	void Print_LEVEL();                      // 레벨출력
};
