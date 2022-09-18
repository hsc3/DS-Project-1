#include "UserList.h"

UserList::UserList()
{
    Root = NULL; // 리스트의 루트노드
}

UserList::~UserList()
{
    delete Root; // 메모리 반납
}

UserListNode* UserList::GetRoot()
{
    return this->Root;
}

AccountBSTNode* UserList::Insert(AccountQueueNode* node)
{
    UserListNode* p = Root; 
    UserListNode* pp = p;
    AccountBSTNode* insertBSTNode = new AccountBSTNode;
    
    // List가 빈 경우 -> 삽입
    if (p == NULL)
    {
        UserListNode* headListNode = new UserListNode;
        headListNode->SetAge(node->GetAge());
        headListNode->SetName(node->GetName());
        Root = headListNode;
        insertBSTNode->SetName(node->GetName());
        insertBSTNode->SetId(node->GetId());
        return Root->InsertAccount(insertBSTNode);
    }
    
    // List가 비지 않은 경우 -> 끝자리 탐색
    else
    {
        while (p != NULL)
        {
            // 동일한 사용자의 노드가 존재. 
            if (strcmp(p->GetName(), node->GetName()) == 0)
            {
                // 계정수 초과 -> 깡통 BST 노드 반환
                if(p->GetAccNum() >= 3)
                {
                    return insertBSTNode;
                }
                // 계정수 초과x -> 계정으로 추가, 카운트
                else
                {
                    break; // p <- 사용자의 ListNode
                }
                
            }
            pp = p;
            p = p->GetNext();
        }
    }
    // 새로운 ListNode로 삽입
    if (p == NULL)
    {
        UserListNode* newListNode = new UserListNode;
        newListNode->SetName(node->GetName());
        newListNode->SetAge(node->GetAge());
        pp->SetNext(newListNode);
    }
    // 기존의 ListNode에 계정 추가
    insertBSTNode->SetName(node->GetName());
    insertBSTNode->SetId(node->GetId());
    return pp->GetNext()->InsertAccount(insertBSTNode);
}

bool UserList::Search(char* name)
{
    UserListNode* searchNameNode = this->Root;

    while(searchNameNode != NULL)
    {   
        if (strcmp(searchNameNode->GetName(), name) == 0) break;// 중복된 사용자의 이름이 존재 
        else searchNameNode = searchNameNode->GetNext();
    }

    if (searchNameNode == NULL) return false; // 존재x
    
    ofstream flog;
    flog.open("log.txt", ios::app);
    
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

bool UserList::Delete_Account(char* name, char* id)
{
    UserListNode* parentListNode = Root; // 삭제노드의 이전노드
    UserListNode* deleteListNode = Root; // id를 삭제할 사용자노드

    // list에서 해당 사용자의 노드 탐색
    while (deleteListNode != NULL)
    {
        if (strcmp(deleteListNode->GetName(), name) == 0)
        {
            break; // 삭제할 노드 탐색완료.
        }
        parentListNode = deleteListNode;
        deleteListNode = deleteListNode->GetNext();
    }

    // 1. 계정이 1개인 경우 -> list에서 해당 노드의 링크를 제거
    if (deleteListNode->GetAccNum() == 1)
    {   
        // 해당 노드가 list의 첫번째 노드인 경우
        if (deleteListNode == parentListNode)
        {
            this->Root = deleteListNode->GetNext();
        }
        else
        {
            parentListNode->SetNext(deleteListNode->GetNext());
        }
        // delete deleteListNode
    }

    // 2. 계정이 2개 이상인 경우 -> 계정수 감소
    else deleteListNode->Delete_Account(id);
    
    return true;
}

void UserList::Print_L(UserListNode* node)
{
    ofstream flog;
    flog.open("log.txt", ios::app);

    while (node != NULL) { // 리스트의 마지막 노드까지 반복

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
        // 사용자의 계정 탐색
        account = p->GetHead();
        while (account != NULL)
        {
            // 계정의 사용자를 찾은 경우, 이름 반환
            if (strcmp(account->GetId(), id) == 0)
                return account->GetName();
            account = account->GetNext(); // 다음 계정으로
        }
        p = p->GetNext(); // 다음 사용자로
    }
    return NULL; // 찾지 못한 경우.
}