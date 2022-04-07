#include "UserInterface.h"
#include "Node.h"
#include "DoubleLinkedList.h"
#include "Algorithm.h"
#include <iostream>
#include <fstream>

using namespace std;

void UserInterface::start(char * argv[]) {
    int choice = 0;

    DoubleLinkedList<int> queue1;
    Algorithm a;

    while(choice != 6) {
        cout << "------ Welcome ------" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Import PCB queue from file" << endl;
        cout << "2. Manually add PCB to queue" << endl;
        cout << "3. Delete PCB from queue" << endl;
        cout << "4. Search Queue for PCB" << endl;
        cout << "5. Print queue" << endl;
        cout << "6. Execute queue" << endl;
        cout << "7. Quit" << endl;
        cout << "Choice: ";
        cin >> choice;
          //displays initial menu and gets user input
        cout << endl;

        while(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice !=7) {
            cout << "Invalid choice, try again!" << endl << endl;
            cout << "------ Welcome ------" << endl;
            cout << "Choose an option:" << endl;
            cout << "1. Import PCB queue from file" << endl;
            cout << "2. Manually add PCB to queue" << endl;
            cout << "3. Delete PCB from queue" << endl;
            cout << "4. Search queue for PCB" << endl;
            cout << "5. Print queue" << endl;
            cout << "6. Execute queue" << endl;
            cout << "7. Quit" << endl;
            cout << "Choice: ";
            cin >> choice;
        }  //redisplay menu until choice = 1 or 2

        if (choice == 1) {
            char* buffer = new char[2048];
            int numlines = 0;
            int tempPID;
            int tempBurst;
            int tempArrival;
            int tempPriority;
            ifstream myFile;
            myFile.open(argv[1]);

            if (myFile.is_open() == false) {
                cout << "Cannot open file target" << endl << endl;
                //checks to make sure file opens properly
            }

            myFile.getline(buffer, 500, '\n');
            numlines = atoi(buffer);
            for (int i = 0; i < numlines; i++) {
                myFile.getline(buffer, 500, ',');
                tempPID = atoi(buffer);
                myFile.getline(buffer, 500, ',');
                tempArrival = atoi(buffer);
                myFile.getline(buffer, 500, ',');
                tempBurst = atoi(buffer);
                myFile.getline(buffer, 500, '\n');
                tempPriority = atoi(buffer);
                queue1.insert(tempPID,tempArrival,tempBurst,tempPriority);
            }
            cout << "PCB successfully inserted!" << endl;
            cout << "Current Queue: ";
            queue1.print();
            cout << endl;
            delete[] buffer;
            myFile.close();
        } else if (choice == 2) {
            int pid;
            int priority;
            int arrivalTime;
            int burstTime;

            cout << "Enter process ID: ";
            cin >> pid;
            cout << "Enter priority: ";
            cin >> priority;
            cout << "Enter arrival time: ";
            cin >> arrivalTime;
            cout << "Enter burst time: ";
            cin >> burstTime;
            queue1.insert(pid,arrivalTime,burstTime,priority);
              //PCB is inserted into queue
            cout << endl << "PCB successfully inserted!" << endl;
            cout << "Current Queue: ";
            queue1.print();
            cout << endl;
        } else if (choice == 3) {
            int pid;

            cout << "Enter process ID for PCB you would like to delete:";
            cin >> pid;
            if(queue1.isElement(pid) == true) {
                queue1.deleteNode(pid);
                  //PCB is deleted from queue
                cout << endl << "PCB successfully deleted!" << endl;
                cout << "Current Queue: ";
                queue1.print();
                cout << endl;
            } else {
                cout << "PCB not found!" << endl << endl;
            }
        } else if (choice == 4) {
            int pid;

            cout << "Enter process id for PCB you would like to search for:";
            cin >> pid;
            if(queue1.isElement(pid) == true) {
                cout << "PCB found!" << endl;
            } else {
                cout << "PCB not found!" << endl << endl;
            }
        } else if (choice == 5) {
            cout << "Current Queue: ";
            queue1.print();
            cout << endl;
        } else if (choice == 6) {
            int tempChoice;
            cout << "Choose an execution algorithm:" << endl;
            cout << "1. Non-Preemptive Priority Scheduling" << endl;
            cout << "2. Preemptive SJF" << endl;
            cout << "Choice: ";
            cin >> tempChoice;
            if(tempChoice == 1) {
                a.priorityScheduling(queue1);
            } else {
                a.preemptiveSJF(queue1);
            }
        } else if (choice == 7) {
                cout << "Program exited" << endl;
                return;
        }
    }
}