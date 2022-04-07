#ifndef COURSE_PROJECT_ALGORITHM_H
#define COURSE_PROJECT_ALGORITHM_H
#include "DoubleLinkedList.h"


class Algorithm {
    public:
        void priorityScheduling(DoubleLinkedList<int>);
        void preemptiveSJF(DoubleLinkedList<int>);
        void findAvgTime(DoubleLinkedList<int>,int);
        void findTurnAroundTime(DoubleLinkedList<int>,int,int[],int[]);
        void findWaitingTime(DoubleLinkedList<int>,int,int[]);
};


#endif //COURSE_PROJECT_ALGORITHM_H
