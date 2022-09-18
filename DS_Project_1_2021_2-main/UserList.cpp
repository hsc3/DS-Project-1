#include "UserList.h"

UserList::UserList()
{
    Root = NULL; // ����Ʈ�� ��Ʈ���
}

UserList::~UserList()
{
    delete Root; // �޸� �ݳ�
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
    
    // List�� �� ��� -> ����
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
    
    // List�� ���� ���� ��� -> ���ڸ� Ž��
    else
    {
        while (p != NULL)
        {
            // ������ ������� ��尡 ����. 
            if (strcmp(p->GetName(), node->GetName()) == 0)
            {
                // ������ �ʰ� -> ���� BST ��� ��ȯ
                if(p->GetAccNum() >= 3)
                {
                    return insertBSTNode;
                }
                // ������ �ʰ�x -> �������� �߰�, ī��Ʈ
                else
                {
                    break; // p <- ������� ListNode
                }
                
            }
            pp = p;
            p = p->GetNext();
        }
    }
    // ���ο� ListNode�� ����
    if (p == NULL)
    {
        UserListNode* newListNode = new UserListNode;
        newListNode->SetName(node->GetName());
        newListNode->SetAge(node->GetAge());
        pp->SetNext(newListNode);
    }
    // ������ ListNode�� ���� �߰�
    insertBSTNode->SetName(node->GetName());
    insertBSTNode->SetId(node->GetId());
    return pp->GetNext()->InsertAccount(insertBSTNode);
}

bool UserList::Search(char* name)
{
    UserListNode* searchNameNode = this->Root;

    while(searchNameNode != NULL)
    {   
        if (strcmp(searchNameNode->GetName(), name) == 0) break;// �ߺ��� ������� �̸��� ���� 
        else searchNameNode = searchNameNode->GetNext();
    }

    if (searchNameNode == NULL) return false; // ����x
    
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
    UserListNode* parentListNode = Root; // ��������� �������
    UserListNode* deleteListNode = Root; // id�� ������ ����ڳ��

    // list���� �ش� ������� ��� Ž��
    while (deleteListNode != NULL)
    {
        if (strcmp(deleteListNode->GetName(), name) == 0)
        {
            break; // ������ ��� Ž���Ϸ�.
        }
        parentListNode = deleteListNode;
        deleteListNode = deleteListNode->GetNext();
    }

    // 1. ������ 1���� ��� -> list���� �ش� ����� ��ũ�� ����
    if (deleteListNode->GetAccNum() == 1)
    {   
        // �ش� ��尡 list�� ù��° ����� ���
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

    // 2. ������ 2�� �̻��� ��� -> ������ ����
    else deleteListNode->Delete_Account(id);
    
    return true;
}

void UserList::Print_L(UserListNode* node)
{
    ofstream flog;
    flog.open("log.txt", ios::app);

    while (node != NULL) { // ����Ʈ�� ������ ������ �ݺ�

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
        // ������� ���� Ž��
        account = p->GetHead();
        while (account != NULL)
        {
            // ������ ����ڸ� ã�� ���, �̸� ��ȯ
            if (strcmp(account->GetId(), id) == 0)
                return account->GetName();
            account = account->GetNext(); // ���� ��������
        }
        p = p->GetNext(); // ���� ����ڷ�
    }
    return NULL; // ã�� ���� ���.
}