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

void Manager::run(const char* command) // ��ɾ� ����
{
    fin.open(command);
    flog.open("log.txt", ios::app);

    if (!fin)
    {
        flog << "File Open Error" << endl;
        return;
    }

    char cmd[32];
    
    while (!fin.eof())
    {
        fin.getline(cmd, 32);
        
        char* tmp[3] = { NULL, };
        int i = 0;
        char* ptr = strtok(cmd, " ");
        while (ptr != NULL)
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
            if (!ADD(tmp[1]))
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

bool Manager::QLOAD() // data.txt ������ �����͸� ť�� �ڵ����� �����Ѵ�.
{
    ifstream fin_data;
    fin_data.open("data.txt");
    if (!ds_queue->EMPTY()) return false; // ť�� �̹� ����

    while (!fin_data.eof())
    {
        char load_data[32];
        fin_data.getline(load_data, 32);
        if (load_data == NULL) return false; // data ���Ͽ� �о�� ������ ���� ���
        
        // �о�� data�� ������
        char* userInformation[3] = { NULL, };
        int i = 0;
        char* ptr = strtok(load_data, " ");
        while (ptr != NULL)
        {
            userInformation[i] = ptr;
            i++;
            ptr = strtok(NULL, " ");
        }

        // �о�� �����͸� �ּҿ� ����
        char* user_name = new char[20];
        char* user_id = new char[20];
        if (userInformation[0] != NULL && userInformation[2] != NULL)
        {
            strcpy(user_name, userInformation[0]);
            strcpy(user_id, userInformation[2]);
        }
        else continue; // �Էµ� data�� �߸��� ���-> ���� data�� �о��

        /********************** ��� ���� **********************/
        AccountQueueNode* loadQueueNode = new AccountQueueNode;
        loadQueueNode->SetName(user_name);
        loadQueueNode->SetAge(atoi(userInformation[1]));
        loadQueueNode->SetId(user_id);

        /********************** ��� ���� **********************/
        ds_queue->PUSH(loadQueueNode); 
    }

    /************************** ť ��� ************************/
    flog << "======= QLOAD =======" << endl;
    ds_queue->PRINT();
    flog << "=====================" << endl << endl;
    fin_data.close();
    return true;
}

bool Manager::ADD(char* parameter) // ť�� ���� �����͸� �߰��Ѵ�.
{
    /****************** ���� ���� ******************/
    char* addInformation[3] = { NULL, };
    int i = 0;
    char* ptr = strtok(parameter, " ");
    while (ptr != NULL)
    {
        addInformation[i] = ptr;
        i++;
        ptr = strtok(NULL, " ");
    }

    // �о�� �����͸� �ּҿ� ����
    char* add_user_name = new char[20];
    char* add_user_id = new char[20];
    if (addInformation[0] != NULL && addInformation[2] != NULL)
    {
        strcpy(add_user_name, addInformation[0]);
        strcpy(add_user_id, addInformation[2]);
    }
    else return false; 
    /******************** ��� ���� *******************/
    AccountQueueNode* addQueueNode = new AccountQueueNode;
    addQueueNode->SetName(add_user_name);
    addQueueNode->SetAge(atoi(addInformation[1]));
    addQueueNode->SetId(add_user_id);

    /******************** ��� ���� *******************/
    ds_queue->PUSH(addQueueNode);  

    /******************* ��� ************************/
    flog << "======= ADD =======" << endl;
    flog << addQueueNode->GetName() << "/" << addQueueNode->GetAge() << "/" << addQueueNode->GetId() << endl;
    flog << "===================" << endl;
    return true;
}

bool Manager::QPOP(int pop_size) // ť�� �����͸� BST�� List�� �ű��.
{
    /********** ť�� �������� ���� �䱸�� ��� **********/
    if (pop_size > ds_queue->SIZE()) return false;
    else
    {
        while (pop_size > 0)
        {

            // ť�� head�� ��ġ�� ��带 POP
            AccountQueueNode* popQueueNode = ds_queue->POP();
            pop_size--;
          
            // 1. List�� ���� �� �����߰� �Ϸ�.
            AccountBSTNode* newBSTNode = ds_list->Insert(popQueueNode);
            // InsertAccount ����
            
            if (newBSTNode->GetName() == NULL)
            {
                PrintErrorCode(301);
                continue;
            }
            else
            {
                // BST ����
                if (!ds_bst->Insert(newBSTNode))
                {
                    ds_list->Delete_Account(newBSTNode->GetName(), newBSTNode->GetId());
                    PrintErrorCode(301);
                    continue;
                }
            }
        }
    }
    return true;
    
}

bool Manager::SEARCH(char* p1, char* p2) // BST�� List�� ����� ������ ã�� ����Ѵ�.
{
    /***************** ID �˻� ******************/
    if (strcmp(p1, "id") == 0 && p2 != NULL)
    {
        if (ds_bst->Search_Id(p2)) return true;// ID�� �ִ� ���
    }
    /*************** User �˻� ******************/
    else if (strcmp(p1, "user") == 0 && p2 != NULL)
    {
        if (ds_list->Search(p2)) return true; // ����ϰ� ��ȯ
    }
    return false; // �߸��� �Է�
}

bool Manager::PRINT(char* structure, char* order) // �ڷᱸ���� ����� �����͵��� ����Ѵ�.
{
    if (strcmp(structure, "L") == 0)
    {
        // ����Ʈ�� �� ���
        if (ds_list->GetRoot() == NULL) return false; 
        
        // ����Ʈ ���
        flog << "======= PRINT ========" << endl << "LIST" << endl;
        ds_list->Print_L(ds_list->GetRoot());
        flog << "=====================" << endl << endl;

    }

    else if (strcmp(structure, "B") == 0)
    {
        if (ds_bst->GetRoot() == NULL) return false; // BST�� �� ���

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
        flog << "===================" << endl <<endl;
    }

    else // Heap ���
    {
        if (ds_heap->GetSize() == 1) return false; // Heap�� �� ���
        
        flog << "======= PRINT =======" << endl <<"Heap" << endl;
        ds_heap->Print();
        flog << "===================" << endl <<endl;
    }
    return true;
}

bool Manager::DELETE(char* deleteId) // �Է¹��� �����͸� List�� BST���� �����Ѵ�.
{
    // ID�� ���� ����ڰ� �����ϴ��� �˻�.
    char* deleteName = ds_list->FindIdUser(deleteId);
    if (deleteName == NULL) return false;

    // List���� �ش� User�� Id�� ����
    ds_list->Delete_Account(deleteName, deleteId);

    // BST���� id�� ����
    ds_bst->Delete(deleteId);

    return true;
}

bool Manager::HLOAD() // List�� �����͸� ������� Heap�� �����Ѵ�.
{
    // List�� ������� ��� ����
    if (ds_list->GetRoot() == NULL) return false;
    else
    {
        ds_heap = new UserHeap; // Heap �ʱ�ȭ
        // User_List�� ��带 1���� �о� Heap�� �Է�
        UserListNode* loadListNode = ds_list->GetRoot();
        while (loadListNode != NULL)
        {
            // �� ��� ���� �� ������
            ds_heap->Insert((loadListNode->GetAge() / 10) * 10);
            loadListNode = loadListNode->GetNext();
        }
    }
    return true;
}

bool Manager::EXIT() // �޸𸮸� �����ϰ�, ���α׷��� ����
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
    flog << "===================" << endl << endl;
}