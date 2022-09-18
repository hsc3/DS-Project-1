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

void Manager::run(const char* command) // 명령어 실행
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

bool Manager::QLOAD() // data.txt 파일의 데이터를 큐에 자동으로 저장한다.
{
    ifstream fin_data;
    fin_data.open("data.txt");
    if (!ds_queue->EMPTY()) return false; // 큐가 이미 존재

    while (!fin_data.eof())
    {
        char load_data[32];
        fin_data.getline(load_data, 32);
        if (load_data == NULL) return false; // data 파일에 읽어올 정보가 없는 경우
        
        // 읽어온 data를 나누기
        char* userInformation[3] = { NULL, };
        int i = 0;
        char* ptr = strtok(load_data, " ");
        while (ptr != NULL)
        {
            userInformation[i] = ptr;
            i++;
            ptr = strtok(NULL, " ");
        }

        // 읽어온 데이터를 주소에 저장
        char* user_name = new char[20];
        char* user_id = new char[20];
        if (userInformation[0] != NULL && userInformation[2] != NULL)
        {
            strcpy(user_name, userInformation[0]);
            strcpy(user_id, userInformation[2]);
        }
        else continue; // 입력된 data가 잘못된 경우-> 다음 data를 읽어옴

        /********************** 노드 생성 **********************/
        AccountQueueNode* loadQueueNode = new AccountQueueNode;
        loadQueueNode->SetName(user_name);
        loadQueueNode->SetAge(atoi(userInformation[1]));
        loadQueueNode->SetId(user_id);

        /********************** 노드 삽입 **********************/
        ds_queue->PUSH(loadQueueNode); 
    }

    /************************** 큐 출력 ************************/
    flog << "======= QLOAD =======" << endl;
    ds_queue->PRINT();
    flog << "=====================" << endl << endl;
    fin_data.close();
    return true;
}

bool Manager::ADD(char* parameter) // 큐에 직접 데이터를 추가한다.
{
    /****************** 인자 분할 ******************/
    char* addInformation[3] = { NULL, };
    int i = 0;
    char* ptr = strtok(parameter, " ");
    while (ptr != NULL)
    {
        addInformation[i] = ptr;
        i++;
        ptr = strtok(NULL, " ");
    }

    // 읽어온 데이터를 주소에 저장
    char* add_user_name = new char[20];
    char* add_user_id = new char[20];
    if (addInformation[0] != NULL && addInformation[2] != NULL)
    {
        strcpy(add_user_name, addInformation[0]);
        strcpy(add_user_id, addInformation[2]);
    }
    else return false; 
    /******************** 노드 생성 *******************/
    AccountQueueNode* addQueueNode = new AccountQueueNode;
    addQueueNode->SetName(add_user_name);
    addQueueNode->SetAge(atoi(addInformation[1]));
    addQueueNode->SetId(add_user_id);

    /******************** 노드 삽입 *******************/
    ds_queue->PUSH(addQueueNode);  

    /******************* 출력 ************************/
    flog << "======= ADD =======" << endl;
    flog << addQueueNode->GetName() << "/" << addQueueNode->GetAge() << "/" << addQueueNode->GetId() << endl;
    flog << "===================" << endl;
    return true;
}

bool Manager::QPOP(int pop_size) // 큐의 데이터를 BST와 List로 옮긴다.
{
    /********** 큐의 개수보다 많이 요구한 경우 **********/
    if (pop_size > ds_queue->SIZE()) return false;
    else
    {
        while (pop_size > 0)
        {

            // 큐의 head에 위치한 노드를 POP
            AccountQueueNode* popQueueNode = ds_queue->POP();
            pop_size--;
          
            // 1. List에 삽입 및 계정추가 완료.
            AccountBSTNode* newBSTNode = ds_list->Insert(popQueueNode);
            // InsertAccount 실행
            
            if (newBSTNode->GetName() == NULL)
            {
                PrintErrorCode(301);
                continue;
            }
            else
            {
                // BST 삽입
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

bool Manager::SEARCH(char* p1, char* p2) // BST와 List에 저장된 정보를 찾아 출력한다.
{
    /***************** ID 검색 ******************/
    if (strcmp(p1, "id") == 0 && p2 != NULL)
    {
        if (ds_bst->Search_Id(p2)) return true;// ID가 있는 경우
    }
    /*************** User 검색 ******************/
    else if (strcmp(p1, "user") == 0 && p2 != NULL)
    {
        if (ds_list->Search(p2)) return true; // 출력하고 반환
    }
    return false; // 잘못된 입력
}

bool Manager::PRINT(char* structure, char* order) // 자료구조에 저장된 데이터들을 출력한다.
{
    if (strcmp(structure, "L") == 0)
    {
        // 리스트가 빈 경우
        if (ds_list->GetRoot() == NULL) return false; 
        
        // 리스트 출력
        flog << "======= PRINT ========" << endl << "LIST" << endl;
        ds_list->Print_L(ds_list->GetRoot());
        flog << "=====================" << endl << endl;

    }

    else if (strcmp(structure, "B") == 0)
    {
        if (ds_bst->GetRoot() == NULL) return false; // BST가 빈 경우

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

    else // Heap 출력
    {
        if (ds_heap->GetSize() == 1) return false; // Heap이 빈 경우
        
        flog << "======= PRINT =======" << endl <<"Heap" << endl;
        ds_heap->Print();
        flog << "===================" << endl <<endl;
    }
    return true;
}

bool Manager::DELETE(char* deleteId) // 입력받은 데이터를 List와 BST에서 삭제한다.
{
    // ID를 지닌 사용자가 존재하는지 검색.
    char* deleteName = ds_list->FindIdUser(deleteId);
    if (deleteName == NULL) return false;

    // List에서 해당 User의 Id를 삭제
    ds_list->Delete_Account(deleteName, deleteId);

    // BST에서 id를 삭제
    ds_bst->Delete(deleteId);

    return true;
}

bool Manager::HLOAD() // List의 데이터를 기반으로 Heap을 생성한다.
{
    // List가 비어있을 경우 에러
    if (ds_list->GetRoot() == NULL) return false;
    else
    {
        ds_heap = new UserHeap; // Heap 초기화
        // User_List의 노드를 1개씩 읽어 Heap에 입력
        UserListNode* loadListNode = ds_list->GetRoot();
        while (loadListNode != NULL)
        {
            // 힙 노드 삽입 및 재정렬
            ds_heap->Insert((loadListNode->GetAge() / 10) * 10);
            loadListNode = loadListNode->GetNext();
        }
    }
    return true;
}

bool Manager::EXIT() // 메모리를 해제하고, 프로그램을 종료
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