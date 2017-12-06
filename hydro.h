#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "list.h"

#ifndef HYDRO_H
#define HYDRO_H

void displayHeader(); //Displays the introduction screen.

int menu(); //Displays the menu.

int readData(FlowList&); //Reads the years and flows from the input file, and inserts them into the list. Returns number of read items.

void display(FlowList&); //Displays years, and flows, and shows the average and median of the flows in the list.

void addData(FlowList&); //Allows the user to add data to the list.

void removeData(FlowList&); //Allows the user to remove data from the list.

double average(FlowList&); //Returns the average of flow data.

double median (FlowList&); //Returns the median of flow data.

void saveData(FlowList&); //Saves the data to the original input file.

void pressEnter(); //BROKEN


#endif // HYDRO_H
