#ifndef FLOWLIST_H
#define FLOWLIST_H

struct ListItem
{
    int year;
    double flow;
};

struct Node
{
    ListItem item;
    Node *next;
};

class FlowList
{
    public:
        //Constructors
        FlowList(); //Default - Creates empty list.
        FlowList(const FlowList&); //Copy - Creates exact copy
        FlowList& operator=(const FlowList&); //Overloaded = Operator
        ~FlowList(); //Destructor

        //Overloaded << Operator
        friend std::ostream& operator<<(std::ostream& os, const FlowList&); //No longer need print function.

        //Member Functions
        bool insert (const double&, const int&); //Insert new node with new values, preserving order from least to greatest (as wanted).
        void remove (const int&); //Removes selected node.
        int exists (const int&);
        Node* headMLocate();


    private:
        Node* headM;

        void destroy();
        void copy(const FlowList& source);
};

#endif // FLOWLIST_H
