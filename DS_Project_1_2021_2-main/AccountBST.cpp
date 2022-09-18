#include "AccountBST.h"


AccountBST::AccountBST()
{
    Root = NULL;
}

AccountBST::~AccountBST()
{
    delete Root;
}

AccountBSTNode* AccountBST::GetRoot()
{
    return Root;
}
/* Insert a new node to the Binary Search Tree */
bool AccountBST::Insert(AccountBSTNode* node)
{
    AccountBSTNode* parent = this->Root;          // Parent of the new node
    AccountBSTNode* head = this->Root;            // Point for insert the node
    AccountBSTNode* newNode = new AccountBSTNode; // Node that wil be newly inserted

    newNode->SetName(node->GetName());
    newNode->SetId(node->GetId());

    if (head == NULL) Root = newNode;
    else
    {
        while (1)
        {       // go to the right child
            if (*(head->GetId()) < *(newNode->GetId()))
            {
                if (head->GetRight() == NULL)
                {
                    head->SetRight(newNode);
                    break;
                }
                else
                {
                    head = head->GetRight();
                }
            }
            // go to the left child
            else
            {
                if (head->GetLeft() == NULL)
                {
                    head->SetLeft(newNode);
                    break;
                }
                else
                {
                    head = head->GetLeft();
                }

            }
        }
    }
    return true;
}

/* Search the node in BST that has "id" */
bool AccountBST::Search_Id(char* id)
{
    AccountBSTNode* searchIdNode = this->Root;

    // Searching from the Root node to the Leaf node
    while (searchIdNode != NULL)
    {
        if (strcmp(searchIdNode->GetId(), id) == 0) break; // found the node
        else
        {       // searhcing for child node
            searchIdNode = (*id < *(searchIdNode->GetId())) ? searchIdNode->GetLeft() : searchIdNode->GetRight();
        }
    }

    if (searchIdNode == NULL) return false; // cannot found the node

    ofstream flog;
    flog.open("log.txt", ios::app);
    flog << "======= SEARCH =======" << endl << "ID" << endl;
    flog << searchIdNode->GetId() << "/" << searchIdNode->GetName() << endl;
    flog << "======================" << endl << endl;
    flog.close();
    return true;
}

/* Delete the node in BST that has "id" */
bool AccountBST::Delete(char* id)
{
    AccountBSTNode* parentBSTNode = Root; // parent node of delete node
    AccountBSTNode* deleteBSTNode = Root; // node that will be deleted

    // if (parentBSTNode == NULL) return false; // BST is empty

    // searching for the delete node
    while (strcmp(deleteBSTNode->GetId(), id) != 0)
    {
        parentBSTNode = deleteBSTNode;
        deleteBSTNode = (*id < *(deleteBSTNode->GetId())) ? deleteBSTNode->GetLeft() : deleteBSTNode->GetRight();

        // if (deleteBSTNode == NULL) return false; // there is no node that has "id"
    }

    // case 1. delete node has no child node -> just cut the link
    if (deleteBSTNode->GetLeft() == NULL && deleteBSTNode->GetRight() == NULL)
    {
        if (*(parentBSTNode->GetId()) > *id) parentBSTNode->SetLeft(NULL);
        else parentBSTNode->SetRight(NULL);
        // delete deleteBSTNode;
    }

    // case 2. delete node has one child node
    else if (deleteBSTNode->GetLeft() == NULL || deleteBSTNode->GetRight() == NULL)
    {
        // when delete node is the left child of parent node
        if (*(parentBSTNode->GetId()) > *id)
            parentBSTNode->SetLeft((deleteBSTNode->GetLeft() != NULL) ? deleteBSTNode->GetLeft() : deleteBSTNode->GetRight());

        else // when delete node is the right child of parent node
            parentBSTNode->SetRight((deleteBSTNode->GetLeft() != NULL) ? deleteBSTNode->GetLeft() : deleteBSTNode->GetRight());
    }

    // case 3. delete node has two child node -> find the smallest node in right subtree
    else
    {
        AccountBSTNode* prevprev = deleteBSTNode;
        AccountBSTNode* prev = prevprev->GetRight();
        AccountBSTNode* curr = prevprev->GetRight()->GetLeft();

        while (curr != NULL) // go to the smallest node
        {
            prevprev = prev;
            prev = curr;
            curr = curr->GetLeft();
        }

        // curr : 0 , prev : node to be deleted  , prevprev : prev's parent
        deleteBSTNode->SetId(prev->GetId());
        deleteBSTNode->SetName(prev->GetName());
        if (prevprev == deleteBSTNode) prevprev->SetRight(prev->GetRight());
        else prevprev->SetLeft(prev->GetRight());
    }
    return true;
}

/* print the BST in PRE order */
void AccountBST::Print_PRE(AccountBSTNode* node)
{
    ofstream flog;
    flog.open("log.txt", ios::app);
    if (node != NULL)
    {
        flog << node->GetId() << "/" << node->GetName() << endl;
        Print_PRE(node->GetLeft());
        Print_PRE(node->GetRight());
    }
    flog.close();
    return;
}
/* print the BST in IN order */
void AccountBST::Print_IN(AccountBSTNode* node)
{
    ofstream flog;
    flog.open("log.txt", ios::app);
    if (node != NULL)
    {
        Print_IN(node->GetLeft());
        flog << node->GetId() << "/" << node->GetName() << endl;
        Print_IN(node->GetRight());
    }
    flog.close();
    return;
}

/* print the BST in POST order */
void AccountBST::Print_POST(AccountBSTNode* node)
{
    ofstream flog;
    flog.open("log.txt", ios::app);
    if (node != NULL)
    {
        Print_POST(node->GetLeft());
        Print_POST(node->GetRight());
        flog << node->GetId() << "/" << node->GetName() << endl;
    }
    flog.close();
    return;
}

/* print the BST in LEVEL order */
void AccountBST::Print_LEVEL()
{
    queue<AccountBSTNode*> q[100];
    AccountBSTNode* p = this->Root;

    if (p == NULL) return; // BST is empty

    ofstream flog;
    flog.open("log.txt", ios::app);

    q->push(p); // push the node 'p' into the queue

    while (q->size() > 0)
    {
        // pop the first node in the queue
        p = q->front();
        q->pop();

        if (p != NULL)
        {
            flog << p->GetId() << "/" << p->GetName() << endl;

            // push the child nodes of 'p'
            if (p->GetLeft() != NULL) q->push(p->GetLeft());
            if (p->GetRight() != NULL) q->push(p->GetRight());
        }
        else break;
    }
    flog.close();
    return;
}

