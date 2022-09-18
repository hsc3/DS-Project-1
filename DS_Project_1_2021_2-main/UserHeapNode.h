#pragma once
#include <cstring>
#include <queue>
using namespace std;

class UserHeapNode
{
private:
	int NumUser;   
	int AgeGroup;

public:
	UserHeapNode();
	~UserHeapNode();

	int GetNumUser();
	int GetAgeGroup();

	void SetNumUser(int number);
	void SetAgeGroup(int agegroup);
};
