#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "hydro.h"
#include "list.h"

using namespace std;

int main()
{
    displayHeader();
    FlowList List;
    int numRecords = readData(List);

    int quit = 0;

    while(quit == 0)
    {
        system("CLS");
        switch(menu()) //ALL INSTANCES OF system("PAUSE") SHOULD BE REPLACED WITH "pressEnter" FUNCTION.
        {
            case 1:
                {
                    system("CLS");
                    display(List);
                    pressEnter();
                    break;
                }
            case 2:
                {
                    system("CLS");
                    addData(List);
                    pressEnter();
                    break;
                }
            case 3:
                {
                    system("CLS");
                    saveData(List);
                    pressEnter();
                    break;
                }
            case 4:
                {
                    system("CLS");
                    removeData(List);
                    pressEnter();
                    break;
                }
            case 5:
                {
                    cout << "\nProgram Terminated...\n\n";
                    quit = 1;
                    break;
                }
            default:
                cout << "\nInvalid Entry.\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                system("PAUSE");
                break;
        }
    }

    return 0;
}

void displayHeader() //pressEnter() is designed for data entry (2x \n), need to artificially insert a "\n" into buffer here.
{
    cout << "Program: Flow Studies - Fall 2017\n" << "Version: 1.0\n" << "Lab Section: B04\n" << "Produced by: Nathan Moton, Andrew Bright\n\n" << endl;
    system("PAUSE");
}

int readData(FlowList& List) //Reads Data and stores it to a FlowList.
{
    ifstream data;
    data.open("flow.txt");

    if(data.fail()) //If flow.txt fails to open.
    {
        cout << "Failed to open file..." << endl;
        exit(1);
    }

    int counter = 0;
    int year;
    double flow;

    while(!data.eof()) //Copies all values from flow.txt into the list.
    {
        data >> year >> flow;
        if(List.insert(flow, year)){
            counter++;
        }
    }

    data.close();

    return counter;
}

int menu() //Displays menu options.
{
    cout << "Please select one of the following operators:\n" << "   1. Display flow list, average and median\n" << "   2. Add data\n" << "   3. Save data into the file\n" <<
        "   4. Remove data\n" << "   5. Quit\n" << "Enter your choice (1, 2, 3, 4, or 5):\n" << endl;

    int selection;
    cin >> selection;

    return selection;
}

void display(FlowList& List) //Displays average and median values.
{
    cout << List;
    cout << "The average value for flow is: " << average(List) << endl;
    cout << "The median value for flow is: " << median(List) << "\n" << endl << flush;
}

void addData(FlowList &List) //Allows users to add data to the list.
{
    cout << "Please enter a year to add to the list:" << endl;
    int year;
    cin >> year;

    cout << "Please enter the flow (in billions of cubic meters) to add to the list:" << endl;
    double flow;
    cin >> flow;

    if(List.exists(year))
        cout << "\nError: duplicate data.\n" << endl;

    else
    {
        List.insert(flow, year);
        cout << "Successfully added the year: " << year << " with flow: " << flow << "\n" << endl;
    }
}

void removeData(FlowList &List) //To be completed.
{
    cout << "Please enter a year to remove from the list:" << endl;
    int year;
    cin >> year;

    if(List.exists(year))
    {
        List.remove(year);
        cout << "Record was successfully removed.\n" << endl;
    }

    else
        cout << "\nError: No such data.\n" << endl;
}

double average(FlowList &List) //Calculates the average item.flow values of a given list.
{
    Node* traverse = List.headMLocate(); //Because headM is private, we must use a member function to provide a location.
    double average = 0;
    int counter = 0;

    while(traverse != 0) //Loop will end once it reaches a null pointer.
    {
        average += traverse->item.flow;
        counter++;
        traverse = traverse->next;
    }

    return ((double)average/counter);
}

double median(FlowList &List) //Calculates the median of item.flow values of a given list.
{
    Node* traverse = List.headMLocate(); //Because headM is private, we must use a member function to provide a location.
    int counter = 0;
    double median = 0;

    while(traverse != 0) //Determines how many values there are in the list.
    {
        counter++;
        traverse = traverse->next;
    }

    //Checks to see if the number of values in the list is odd or even.
    if (counter % 2 == 0) //If the number of values is even, the median is simply the mean of the two middle numbers.
    {
        int medianLocation = counter/2; //Determines the value of the first middle number.
        traverse = List.headMLocate(); //Resetting the traverse pointer.
        counter = 1; //Reseting the counter.

        while(counter != medianLocation) //Moves the traverse pointer until it reaches the first median location.
        {
            counter++;
            traverse = traverse->next;
        }
        median += traverse->item.flow; //Once it reaches the first median location, it will take it's value and add it to the total median.
        traverse = traverse->next; //Moves to the second median location.
        median += traverse->item.flow; //Adds the second median's location's value.

        return median/2; //Returns the average of the two median center values.

    }

    else //If the number of values is odd, the median can be easily found.
    {
        int medianLocation = counter/2; //Determines the location of the median.
        traverse = List.headMLocate();
        counter = 0;

        while (counter != medianLocation) //Will stop at the median location.
        {
            counter++;
            traverse = traverse->next;
        }
        median = traverse->item.flow;

        return median; //Returns the median value.
    }
}

void saveData(FlowList& List)
{
    Node* traverse = List.headMLocate();

    ofstream data;
    data.open("flow.txt", ofstream::out | ofstream::trunc );

    if(data.fail())
    {
        cout << "Failed to open file..." << endl;
        exit(1);
    }

    while(traverse != 0) //Copies all values from the list into the flow.txt.
    {
        data << traverse->item.year << "      " << traverse->item.flow << endl;
        traverse = traverse->next;
    }
    cout << "Data successfully saved." << endl;
    data.close();
}

void pressEnter()
{
    cout << "\n\n <<<<< Press Enter to Continue. >>>>>\n" << endl;
    cin.ignore(); //Targets the newline character after data entry.
    cin.ignore();
}
