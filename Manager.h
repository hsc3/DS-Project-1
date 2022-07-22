#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "AccountBST.h"
#include "AccountQueue.h"
#include "UserHeap.h"
#include "UserList.h"


class Manager
{
private:
	AccountQueue* ds_queue;
	AccountBST* ds_bst;
	UserHeap* ds_heap;
	UserList* ds_list;
	ifstream fin;
	ofstream flog;

public:
	Manager();
	~Manager();

	void run(const char* command);                // execute commands
	bool QLOAD();                                 // data.txt -> queue
	bool ADD(char* p1, char* p2, char* p3);       // user add -> queue
	bool QPOP(int pop_size);                      // queue -> BST, List
	bool SEARCH(char* p1, char* p2);              // Looking for BST, List and show
	bool PRINT(char* structure, char* order);     // Show each structures
	bool DELETE(char* deleteId);                  // delete data in BST, List
	bool HLOAD();                                 // List -> Heap
	bool EXIT();                                  // free memories, exit

	void PrintErrorCode(int num);
	void PrintSuccess(const char* act);
};
