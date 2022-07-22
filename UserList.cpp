#include "UserList.h"

UserList::UserList()
{
    Root = NULL; 
}

UserList::~UserList()
{
    delete Root; 
}

UserListNode* UserList::GetRoot()
{
    return this->Root;
}

/* Insert a new node into the List */
AccountBSTNode* UserList::Insert(AccountQueueNode* node)
{
    UserListNode* p = Root; 
    UserListNode* pp = p;
    AccountBSTNode* insertBSTNode = new AccountBSTNode;
    
    // when the List is empty  
    if (p == NULL)
    {
        UserListNode* headListNode = new UserListNode;
        headListNode->SetAge(node->GetAge());
        headListNode->SetName(node->GetName());
        Root = headListNode;  // insert a new node into the head of the List
        insertBSTNode->SetName(node->GetName());
        insertBSTNode->SetId(node->GetId());
        return Root->InsertAccount(insertBSTNode);
    }
    
    // when the List isn't empty 
    else
    {
        while (p != NULL) // search for the List  
        {
            // the node that want to insert is already existed 
            if (strcmp(p->GetName(), node->GetName()) == 0)
            {
                // if the node has 3 accounts  
                if(p->GetAccNum() == 3)
                {
                    return insertBSTNode; // return empty node
                }
                // if the has accounts less than 3 
                else
                {
                    break; // return the p that is the node we wanted to find 
                }
                
            }
            pp = p;
            p = p->GetNext();
        }
    }
    // insert the new node into the list 
    if (p == NULL)
    {
        UserListNode* newListNode = new UserListNode;
        newListNode->SetName(node->GetName());
        newListNode->SetAge(node->GetAge());
        pp->SetNext(newListNode);
    }
    // insert the new account into the list node  
    insertBSTNode->SetName(node->GetName());
    insertBSTNode->SetId(node->GetId());
    return pp->GetNext()->InsertAccount(insertBSTNode);
}

/* Search for the "name" in the list */
bool UserList::Search(char* name)
{
    UserListNode* searchNameNode = this->Root;

    while(searchNameNode != NULL)
    {   
        if (strcmp(searchNameNode->GetName(), name) == 0) break;// found the node that has "name" 
        else searchNameNode = searchNameNode->GetNext();
    }

    if (searchNameNode == NULL) return false; // cannot found the "name" 
    
    ofstream flog;
    flog.open("log.txt", ios::app);
   
    // print the all accounts that the node is have 
    AccountBSTNode* searchAccount = searchNameNode->GetHead();
    flog << "======= SEARCH =======" << endl << "User" << endl;
    flog << searchNameNode->GetName() << "/" << searchNameNode->GetAge() << endl;
    while (searchAccount != NULL)
    {
        flog << searchAccount->GetId() << endl;
        searchAccount = searchAccount->GetNext();
    }
    flog << "======================" << endl <<endl;
    flog.close();
    return true;
}

/* Delete the account of the list node that has "name" and "id" */
bool UserList::Delete_Account(char* name, char* id)
{
    UserListNode* parentListNode = Root; // parent of the delete list node 
    UserListNode* deleteListNode = Root; // the list node that can be deleted (0 account) 

    // search for the list 
    while (deleteListNode != NULL)
    {
        if (strcmp(deleteListNode->GetName(), name) == 0)
        {
            break; // found the node 
        }
        parentListNode = deleteListNode;
        deleteListNode = deleteListNode->GetNext();
    }

    // case 1. if the node has only 1 account 
    if (deleteListNode->GetAccNum() == 1)
    {   
        // when the list node is the head node  
        if (deleteListNode == parentListNode)
        {
            this->Root = deleteListNode->GetNext();
        }
        // when the list node isn't the head node -> just cut the link
        else
        {
            parentListNode->SetNext(deleteListNode->GetNext());
        }
        // delete deleteListNode
    }

    // case 2. if the node has accounts more than 1 -> delete the account 
    else deleteListNode->Delete_Account(id);
    
    return true;
}

/* Print the List */
void UserList::Print_L(UserListNode* node)
{
    ofstream flog;
    flog.open("log.txt", ios::app);

    while (node != NULL) 
    { 

        flog << node->GetName() << "/" << node->GetAge() << "/" << node->GetAccNum() << endl;
        node = node->GetNext();
    }
    flog.close();
    return;
}


char* UserList::FindIdUser(char* id)
{
    UserListNode* p = Root;
    AccountBSTNode* account = NULL;
    while (p != NULL)
    {
        // search for the all accounts 
        account = p->GetHead();
        while (account != NULL)
        {
            // return the user name that has "id" 
            if (strcmp(account->GetId(), id) == 0)
                return account->GetName();
            account = account->GetNext(); 
        }
        p = p->GetNext();
    }
    return NULL; // there is no user that has "id"  
}
