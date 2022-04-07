#include "Algorithm.h"
#include "DoubleLinkedList.h"
#include "Node.h"
#include <iostream>

using namespace std;

void Algorithm::priorityScheduling(DoubleLinkedList<int> queue1) {
    int wt[queue1.getSize()], tat[queue1.getSize()], ct[queue1.getSize()];
    int total = 0;
    int total_wt = 0;
    int total_tat = 0;

    Node<int> *iterator;
    iterator = queue1.getHead();
      //initializes iterator to the head

    for (int i = 0; i < queue1.getSize(); i++) {
        if(iterator->getArrivalTime() <= total) {
            ct[i] = total + iterator->getBurstTime();
        } else {
            int timeTilArrival = total - iterator->getArrivalTime();
            ct[i] = total + iterator->getBurstTime() + timeTilArrival;
        }  //calculates total completion time
        tat[i] = ct[i] - iterator->getArrivalTime();
          //calculates turnaround time
        wt[i] = tat[i] - iterator->getBurstTime();
          //calculates wait time
        total = total + tat[i];

        iterator = iterator->getNext();
    }

    cout << endl << "Processes " << " Burst time " << " Waiting time " << " Turn around time\n";

    Node<int> *iterator1;
    iterator1 = queue1.getHead();
      //initializes iterator to the head

    for(int i = 0; i < queue1.getSize(); i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << iterator1->getPID() << "\t\t" << iterator1->getBurstTime() << "\t\t " << wt[i] << "\t\t " << tat[i] << endl;
        iterator1 = iterator1->getNext();
    }

    cout << "\nAverage waiting time = " << (float)total_wt / (float)queue1.getSize(); cout << "\nAverage turn around time = " << (float)total_tat / (float)queue1.getSize() << endl;

}

void Algorithm::preemptiveSJF(DoubleLinkedList<int> queue1) {
    findAvgTime(queue1,queue1.getSize());
}

void Algorithm::findAvgTime(DoubleLinkedList<int> queue1, int n) {
    int wt[n], tat[n], total_wt = 0,
            total_tat = 0;

    findWaitingTime(queue1, n, wt);
      //finds the waiting time for each process
    findTurnAroundTime(queue1, n, wt, tat);
      //finds the turn around time for each process
    cout << endl << "Processes " << " Burst time " << " Waiting time " << " Turn around time\n";

    Node<int> *iterator;
    iterator = queue1.getHead();
      //initializes iterator to the head

    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << iterator->getPID() << "\t\t" << iterator->getBurstTime() << "\t\t " << wt[i] << "\t\t " << tat[i] << endl;
        iterator = iterator->getNext();
    }
    cout << "\nAverage waiting time = " << (float)total_wt / (float)n; cout << "\nAverage turn around time = " << (float)total_tat / (float)n << endl;
}

void Algorithm::findTurnAroundTime(DoubleLinkedList<int> queue1, int n, int wt[], int tat[]) {
    Node<int> *iterator;
    iterator = queue1.getHead();
      //initializes iterator to the head

    for (int i = 0; i < n; i++) {
        tat[i] = iterator->getBurstTime() + wt[i];
        iterator = iterator->getNext();
    }
}

void Algorithm::findWaitingTime(DoubleLinkedList<int> queue1, int n, int wt[]) {
    int rt[n];
    Node<int> *iterator;
    iterator = queue1.getHead();
      //initializes iterator to the head

    for (int i = 0; i < n; i++) {
        rt[i] = iterator->getBurstTime();
        iterator = iterator->getNext();
    }
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, shortestPID, finish_time;
    bool check = false;
    while (complete != n) {
        Node<int> *iterator1;
        iterator1 = queue1.getHead();
          //initializes iterator to the head
        for (int j = 0; j < n; j++) {
            if ((iterator1->getArrivalTime() <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                shortestPID = iterator1->getPID();
                check = true;
            }
            iterator1 = iterator1->getNext();
        }
        if (check == false) {
            t++;
            continue;
        }
        // decrementing the remaining time
        rt[shortest]--;
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;
        // If a process gets completely
        // executed
        if (rt[shortest] == 0) {
            complete++;
            check = false;
            finish_time = t + 1;
            Node<int> *temp = queue1.getElement(shortestPID);
            // Calculate waiting time
            wt[shortest] = finish_time -
                           temp->getBurstTime() -
                           temp->getArrivalTime();
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        // Increment time
        t++;
    }
}