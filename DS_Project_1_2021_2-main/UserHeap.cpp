#include "UserHeap.h"

UserHeap::UserHeap()
{
    Heap.clear();
    UserHeapNode* emptyHeapNode = new UserHeapNode;
    emptyHeapNode->SetAgeGroup(0);
    emptyHeapNode->SetNumUser(0);
    Heap.push_back(emptyHeapNode);
}

UserHeap::~UserHeap()
{
    Heap.~vector();
}

bool UserHeap::Insert(int agegroup) // ���� �� ������
{
    // ����
    bool check_exist = false;
    int i;
    // �� üũ
    for (i = 1; i < Heap.size(); i++)
    {
        if (Heap[i]->GetAgeGroup() == agegroup)
        {
            check_exist = true;
            break;
        }
    }
    // ���� ���̴밡 �ִ� ���.
    if (check_exist == true)
    {
        Heap[i]->SetNumUser(Heap[i]->GetNumUser() + 1);
        // ������
        // this->Sort();
    }
    // ���� ���̴밡 ���� ���.
    else
    {
        UserHeapNode* newHeapNode = new UserHeapNode;
        newHeapNode->SetNumUser(1);
        newHeapNode->SetAgeGroup(agegroup);
        Heap.push_back(newHeapNode);
    }

    Sort();
    return true;
}

void UserHeap::Print()
{
    ofstream flog;
    flog.open("log.txt", ios::app);

	for (int i = 1; i < Heap.size(); i++) 
    {
        flog << Heap[i]->GetNumUser() << "/" << Heap[i]->GetAgeGroup() << endl;
	}
    flog.close();
    return;
}

void UserHeap::Sort()
{
    int child = Heap.size() - 1;
    int parent = child / 2;
 
    while (child > 1 && Heap[parent]->GetNumUser() < Heap[child]->GetNumUser())
    {
        swap(Heap[parent], Heap[child]);

        child = parent;
        parent = parent / 2;
    }
    return;
}

int UserHeap::GetSize()
{
    return this->Heap.size();
}