#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

template <typename T>
class Node {
    template <class U> friend class DoubleLinkedList;
private:
    Node<T>* next;
    Node<T>* prev;
    int pid;
    int priority;
    int arrivalTime;
    int burstTime;
public:
    Node():next(nullptr),prev(nullptr){}
      //default constructor
    Node(int w, int x, int y, int z):next(nullptr),prev(nullptr),pid(w),arrivalTime(x),burstTime(y),priority(z){}
      //overloaded constructor
    Node(const Node<T>* const& x):next(x->next),prev(x->prev),pid(x->pid),arrivalTime(x->arrivalTime),burstTime(x->burstTime),priority(x->priority){}
      //overloaded constructor
    Node<T> operator=(const Node<T>* const&x);
      //overloaded equals operator
    int& getPID();
    int& getPriority();
    int& getArrivalTime();
    int& getBurstTime();
    Node<T>* getNext();
    Node<T>* getPrev();
};

template <typename T>
Node<T> Node<T>::operator=(const Node<T> *const &x) {
    Node<T> temp = new Node(x);

    return temp;
}

template <typename T>
int& Node<T>::getPID() {
    return this->pid;
}

template <typename T>
int& Node<T>::getPriority() {
    return this->priority;
}

template <typename T>
int& Node<T>::getArrivalTime() {
    return this->arrivalTime;
}

template <typename T>
int& Node<T>::getBurstTime() {
    return this->burstTime;
}

template <typename T>
Node<T>* Node<T>::getNext() {
    return this->next;
}

template <typename T>
Node<T>* Node<T>::getPrev() {
    return this->prev;
}

#endif
