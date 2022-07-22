#include "UserHeapNode.h"
UserHeapNode::UserHeapNode()
{
	NumUser = 0;
	AgeGroup = 0;
}

UserHeapNode::~UserHeapNode()
{

}

int UserHeapNode::GetNumUser()
{
	return this->NumUser;
}

int UserHeapNode::GetAgeGroup()
{
	return this->AgeGroup;
}

void UserHeapNode::SetNumUser(int number)
{
	this->NumUser = number;
}

void UserHeapNode::SetAgeGroup(int agegroup)
{
	this->AgeGroup = agegroup;
}
