#include "Manager.h"

Manager::Manager()
{
    this->ds_queue = new AccountQueue; 
    this->ds_bst = new AccountBST;
    this->ds_list = new UserList;
    this->ds_heap = new UserHeap;
}

Manager::~Manager()
{
 
}

void Manager::run(const char* command)
{
    fin.open(command);
    flog.open("log.txt", ios::app);

    if (!fin)
    {
        flog << "File Open Error" << endl;
        return;
    }

    char cmd[32];
    
    while (!fin.eof()) // read all commands
    {
        fin.getline(cmd, 32);
       
        // make parameters for behind functions
        char* tmp[4] = { NULL, };
        int i = 0;
        char* ptr = strtok(cmd, " ");
        while (ptr != NULL) // tokenize the command 
        {
            tmp[i] = ptr;
            i++;
            ptr = strtok(NULL, " ");
        }

        if(strcmp(tmp[0], "QLOAD") == 0)
        {
            if(!QLOAD())
            {
                PrintErrorCode(100);
            }
        }
        else if (strcmp(tmp[0], "ADD") == 0)
        {
            if (!ADD(tmp[1], tmp[2], tmp[3]))
            {
                PrintErrorCode(200);
            }
        }
        else if (strcmp(tmp[0], "QPOP") == 0) 
        {
            if (QPOP(atoi(tmp[1])))
            {
                PrintSuccess("QPOP");
            }
            else
            {
                PrintErrorCode(300);
            }
        }
        else if (strcmp(tmp[0], "SEARCH") == 0)
        {
            if (!SEARCH(tmp[1],tmp[2]))
            {
                PrintErrorCode(400);
            }
        }
        else if (strcmp(tmp[0], "PRINT") == 0)
        {
            // B or L or H
            
            if (!PRINT(tmp[1], tmp[2]))
            {
                PrintErrorCode(500);
            }
        }
        else if (strcmp(tmp[0], "DELETE") == 0)
        {
            if (DELETE(tmp[1]))
            {
                PrintSuccess("DELETE");
            }
            else
            {
                PrintErrorCode(600);
            }
        }
        else if (strcmp(tmp[0], "HLOAD") == 0)
        {
            if (HLOAD())
            {
                PrintSuccess("HLOAD");
            }
            else
            {
                PrintErrorCode(700);
            }
        }
        else if(strcmp(tmp[0], "EXIT") == 0)
        {
            PrintSuccess("EXIT");
            break;
        }
        else
        {
            PrintErrorCode(800);
        }
    }
    fin.close();
    flog.close();
    return;
}

/* Load data file and make a queue */
bool Manager::QLOAD() 
{
    ifstream fin_data;
    fin_data.open("data.txt");
    if (!ds_queue->EMPTY()) return false; // if the queue is already exist  

    while (!fin_data.eof())
    {
        char load_data[32];
        fin_data.getline(load_data, 32);
        if (load_data == NULL) return false; // if there is no data 
        
        // tokenize the data for user's name, age, id 
        char* userInformation[3] = { NULL, };
        int i = 0;
        char* ptr = strtok(load_data, " ");
        while (ptr != NULL)
        {
            userInformation[i] = ptr;
            i++;
            ptr = strtok(NULL, " ");
        }
        
        // save the tokenized datas into memory address
        char* user_name = new char[20];
        char* user_id = new char[20];
        if(userInformation[0] != NULL && userInformation[1] != NULL && userInformation[2] != NULL)
        {
            strcpy(user_name, userInformation[0]);   
            strcpy(user_id, userInformation[2]);
        }
        else continue; // load next data (input data is not complete) 

        // make a new queue node
        AccountQueueNode* loadQueueNode = new AccountQueueNode;
        loadQueueNode->SetName(user_name);
        loadQueueNode->SetAge(atoi(userInformation[1]));
        loadQueueNode->SetId(user_id);

        // push the node into the queue
        ds_queue->PUSH(loadQueueNode); 
    }

    // print the result
    flog << "======== QLOAD ========" << endl;
    ds_queue->PRINT();
    flog << "=======================" << endl << endl;
    fin_data.close();
    return true;
}

/* Add a queue node based on user's direct input */ 
bool Manager::ADD(char* p1, char* p2, char* p3) 
{
    // if input datas are not complete
    if (p1 == NULL || p2 == NULL || p3 == NULL)
    {
    	return false;
    }
    
    // save the datas into memory address
        char* add_name = new char[20];
        char* add_id = new char[20];
        strcpy(add_name, p1);
        strcpy(add_id, p3);
       
    // make a new queue node 
    AccountQueueNode* addQueueNode = new AccountQueueNode;
    addQueueNode->SetName(add_name);
    addQueueNode->SetAge(atoi(p2));
    addQueueNode->SetId(add_id);

    // push into the queue
    ds_queue->PUSH(addQueueNode);  

    // print the result
    flog << "======== ADD ========" << endl;
    flog << addQueueNode->GetName() << "/" << addQueueNode->GetAge() << "/" << addQueueNode->GetId() << endl;
    flog << "=====================" << endl << endl;
    return true;
}

/* Pop the queue nodes and make List and BST */ 
bool Manager::QPOP(int pop_size) 
{
    // if the input "pop_size" is bigger than the queue size
    if (pop_size > ds_queue->SIZE()) return false;
    
    else
    {
        while (pop_size > 0)
        {

            // Pop the queue node
            AccountQueueNode* popQueueNode = ds_queue->POP();
            pop_size--;
          
            // 1. make the List and also insert user's account to the list node  
            AccountBSTNode* newBSTNode = ds_list->Insert(popQueueNode);
            
            if (newBSTNode->GetName() == NULL) // process 1 is failed (the user has more than 3 accounts) 
            {
                PrintErrorCode(301);
                continue;
            }

            else
            {
                // 2. make the BST 
                if (!ds_bst->Insert(newBSTNode))
                {
                    ds_list->Delete_Account(newBSTNode->GetName(), newBSTNode->GetId());
                    PrintErrorCode(301); // process 2 is failed (there is same account)   
                    continue;
                }
            }
        }
    }
    return true;
    
}

/* Search for ID or User */ 
bool Manager::SEARCH(char* p1, char* p2) 
{
    // search for the ID 
    if (strcmp(p1, "id") == 0 && p2 != NULL)
    {
        if (ds_bst->Search_Id(p2)) return true;
    }
    
    // search for the User 
    else if (strcmp(p1, "user") == 0 && p2 != NULL)
    {
        if (ds_list->Search(p2)) return true; 
    }
    return false; 
}

/* Print the List, BST, or Heap */
bool Manager::PRINT(char* structure, char* order) 
{
    if (strcmp(structure, "L") == 0)
    {
        // if the list is empty 
        if (ds_list->GetRoot() == NULL) return false; 
        
        // print the list 
        flog << "======= PRINT ========" << endl << "LIST" << endl;
        ds_list->Print_L(ds_list->GetRoot());
        flog << "======================" << endl << endl;

    }

    else if (strcmp(structure, "B") == 0)
    {
        // if the BST is empty
        if (ds_bst->GetRoot() == NULL) return false; 

        // print the BST based on PRE, IN, POST, LEVEL order
        flog << "======= PRINT =======" << endl;
        if (strcmp(order, "PRE") == 0)
        {
            flog << "BST PRE" << endl;
            ds_bst->Print_PRE(ds_bst->GetRoot());
        }
        else if (strcmp(order, "IN") == 0)
        {
            flog << "BST IN" << endl;
            ds_bst->Print_IN(ds_bst->GetRoot());
        }
        else if (strcmp(order, "POST") == 0)
        {
            flog << "BST POST" << endl;
            ds_bst->Print_POST(ds_bst->GetRoot());
        }
        else // LEVEL 
        {
            flog << "BST LEVEL" << endl;
            ds_bst->Print_LEVEL();
        }
        flog << "=====================" << endl <<endl;
    }

    else // print the Heap 
    {   
        // if the Heap is empty
        if (ds_heap->GetSize() == 1) return false;  
       
        // print the Heap 
        flog << "======= PRINT =======" << endl <<"Heap" << endl;
        ds_heap->Print();
        flog << "=====================" << endl <<endl;
    }
    return true;
}

/* Delete the node */
bool Manager::DELETE(char* deleteId) 
{
    // find the user that has "deleteId" 
    char* deleteName = ds_list->FindIdUser(deleteId);
    if (deleteName == NULL) return false;

    // delete in the list based on the number of accounts  
    ds_list->Delete_Account(deleteName, deleteId);

    // delete in the BST 
    ds_bst->Delete(deleteId);

    return true;
}

/* Make a Heap based on the userList */
bool Manager::HLOAD() 
{
    // if the list is empty 
    if (ds_list->GetRoot() == NULL) return false;
    
    else
    {
        ds_heap = new UserHeap; // Initialize the Heap­
        UserListNode* loadListNode = ds_list->GetRoot();
        while (loadListNode != NULL)
        {
            // insert to the Heap based on calculated age group 
            ds_heap->Insert((loadListNode->GetAge() / 10) * 10);
            loadListNode = loadListNode->GetNext();
        }
    }
    return true;
}

/* de-allocate all sources and exit */ 
bool Manager::EXIT() 
{
    delete ds_queue;
    delete ds_bst;
    delete ds_heap;
    delete ds_list;
    fin.close();
    flog.close();
    return true;
}

void Manager::PrintErrorCode(int num)
{
    flog << "======= ERROR =======" << endl;
    flog << num << endl;
    flog << "=====================" << endl << endl;
}

void Manager::PrintSuccess(const char* act)
{
    flog << "======= " << act << " =======" << endl;
    flog << "Success" << endl;
    flog << "=====================" << endl << endl;
}
