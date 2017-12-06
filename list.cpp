#include <iostream>
#include <stdlib.h>
#include "list.h"

using namespace std;

FlowList::FlowList()
:headM(0)
{
}

FlowList::FlowList(const FlowList& source)
{
    copy(source);
}

FlowList& FlowList::operator=(const FlowList& rhs)
{
    if(this != &rhs)
        copy(rhs);

    return *this;
}

bool FlowList::insert(const double& inserted_flow, const int& inserted_year)
{
    Node* inserted_node = new Node;
    inserted_node->item.flow = inserted_flow;
    inserted_node->item.year = inserted_year;

    if (headM == 0 || inserted_flow <= headM->item.flow)
    {
        inserted_node->next = headM;
        headM = inserted_node;
        return true;
    }
    else if(exists(inserted_year) != 1)
    {
        Node* before = headM;
        Node* after = headM->next;

        while(after != 0 && inserted_flow > after->item.flow)
        {
            before = after;
            after = after->next;
        }

        before->next = inserted_node;
        inserted_node->next = after;
        return true;
    }
    else
    {
        return false;
    }
}

void FlowList::remove(const int& removed_year)
{
    //Code was modified to check for flow. I would prefer if it removed a specific year's data rather than a specific flow.
    if (headM == 0)
        return;

    Node *doomed_node = 0;

    if (removed_year == headM->item.year)
    {
        doomed_node = headM;
        headM = headM->next;
    }

    else
    {
        Node *before = headM;
        Node *maybe_doomed = headM->next;
        while(maybe_doomed != 0 && removed_year != maybe_doomed->item.year) {
            before = maybe_doomed;
            maybe_doomed = maybe_doomed->next;
        }
    //Start of Nathan's Code:

    //The above while loop will find the matching node to delete and point to it as "maybe_doomed".
    doomed_node = maybe_doomed; //Setting doomed_node.
    maybe_doomed = maybe_doomed->next; //Changing the maybe_doomed pointer to the pointer after it.
    before->next = maybe_doomed;

    delete doomed_node;
    }
}

int FlowList::exists(const int& year)
{
    Node* traverse = headM;

    while(traverse != 0)
    {
        if (year == traverse->item.year)
            return 1;
        traverse = traverse->next;
    }

    return 0;
}

Node* FlowList::headMLocate()
{
    return headM;
}

void FlowList::destroy()
{
    Node* to_destroy = 0;

    while (headM != 0)
    {
        to_destroy = headM;
        headM = headM->next;
        delete to_destroy;
    }
    delete headM;
}

void FlowList::copy(const FlowList& source)
{
    //If source's headM is a null pointer, the duplicate headM will also be a null pointer.
    if (source.headM == 0)
        headM = 0;

    else
    {
        //Creating a node called new_head. This will be the duplicate of the source's headM node.
        Node* new_head = new Node;
        new_head->item.flow = source.headM->item.flow; //Copying the value of source's headM's node's item, into the duplicate's headM's node's item.
        new_head->item.year = source.headM->item.year;
        new_head-> next = 0;

        //Pointing the duplicate's headM to new_head.
        headM = new_head;


        //Creating a pair of traversing before and after pointers. The "S" stands for "source".
        Node* traverseS_be = source.headM; //The before pointer will point to the source's headM node.
        Node* traverseS_af = source.headM->next; //The after pointer will point to the next node source's headM is pointing to.


        //Creating a traversing before pointer. The "D" stands for "duplicate".
        Node* traverseD_be = new_head; //The before pointer will point to the duplicate's headM node.

        while (traverseS_af != 0)
        {
         //Moving the source traverse pointers forward.
         traverseS_be = traverseS_af;
         traverseS_af = traverseS_af->next;

         //Creating a new node that will be a copy of the source's before pointer.
         Node* new_node = new Node;
         new_node->item.flow = traverseS_be->item.flow;
         new_node->item.year = traverseS_be->item.year;
         new_node->next = 0; //Setting the next pointer to be a null pointer as a precaution.

         traverseD_be->next = new_node;
         traverseD_be = new_node;

        }
    }
}

FlowList::~FlowList()
{
    destroy();
}

std::ostream& operator<<(std::ostream& os, const FlowList &List)
{
    os << "Year:" << "      " << "Flow (in billions of cubic meters):" << std::endl;
    os << "-----" << "      " << "-----------------------------------" << std::endl;
    os << List.headM->item.year << "         " << List.headM->item.flow << std::endl;

    for (const Node *p = List.headM->next; p!= 0; p = p->next)
        os << p->item.year << "         " << p->item.flow << std::endl;
}

