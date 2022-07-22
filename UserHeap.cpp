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

/* Insert a heap node */
bool UserHeap::Insert(int agegroup)
{
      
    bool check_exist = false;
    int i;
   
    // check the "agegroup" is already exist 
    for (i = 1; i < Heap.size(); i++)
    {
        if (Heap[i]->GetAgeGroup() == agegroup)
        {
            check_exist = true;
            break;
        }
    } 

    // already exist -> increase the number of user 
    if (check_exist == true)
    {
        Heap[i]->SetNumUser(Heap[i]->GetNumUser() + 1);
    }

    // not exist -> insert the new heap node 
    else
    {
        UserHeapNode* newHeapNode = new UserHeapNode;
        newHeapNode->SetNumUser(1);
        newHeapNode->SetAgeGroup(agegroup);
        Heap.push_back(newHeapNode);
    }

    Sort();  // re-sort the heap
    return true;
}

/* Print the heap */
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

/* Function for sort the heap */
void UserHeap::Sort()
{
    int child = Heap.size() - 1; // index for child heap node
    int parent = child / 2;      // index for parent heap node
 
    while (child > 1 && Heap[parent]->GetNumUser() < Heap[child]->GetNumUser())
    {
        swap(Heap[parent], Heap[child]); // swap location of two nodes

        child = parent;
        parent = parent / 2;
    }
    return;
}

/* return size of the heap */
int UserHeap::GetSize()
{
    return this->Heap.size();
}
