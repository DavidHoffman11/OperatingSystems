#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "Node.h"
#include <iostream>

using namespace std;

template<typename T>
class DoubleLinkedList {
    private:
        Node<T> *head;
        Node<T> *tail;
        int size;
    public:
        DoubleLinkedList();
          //default constructor
        DoubleLinkedList(const DoubleLinkedList<T> &);
          //copy constructor
        ~DoubleLinkedList();
          //destructor
        void insert(int);
          //inserts item at pack of list
        void insert(int pid, int arrivalTime, int burstTime, int priority);
          //inserts item based off priority
        void deleteNode(int pid);
          //deletes a specific node from list
        bool isElement(T);
          //checks to see if an object is already an element of the list
        Node<T>* getElement(int);
          //returns the PCB with a given process id
        void print();
          //prints the list
        Node<T> *getHead();
          //returns data of head
        Node<T> *getTail();
          //returns data of tail
        int getSize();
          //returns size
};

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList() {
    this->size = 0;
    this->head = NULL;
    this->tail = NULL;
}  //default constructor

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T> &x) {
    head = new Node<T>(x.head);
    Node<T> *iterator;

    iterator = head;
    //initializes iterator to the top of the linked list

    size = x.size;

    while (iterator->next != nullptr) {
        iterator->next = new Node<T>(iterator->next);
        iterator = iterator->next;
        if(iterator->next == nullptr) {
            tail = iterator;
        }
    }  //adds every node in the linked list x to another linked list
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {

}  //destructor

template<typename T>
void DoubleLinkedList<T>::insert(int pid) {
    Node<T> *node = new Node<T>(pid, this->size + 1);

    if (this->size == 0) {
        node->next = nullptr;
        node->prev = nullptr;
        this->head = node;
        this->tail = node;
        this->size++;
    } else {
        node->next = nullptr;
        node->prev = this->tail;
        this->tail->next = node;
        //sets next value equal to a nullptr and prev value equal to the former tail
        this->tail = node;
        //makes the new node the new tail
        this->size++;
    }
}

template<typename T>
void DoubleLinkedList<T>::insert(int pid, int arrivalTime, int burstTime, int priority) {
    Node<T> *node = new Node<T>(pid, arrivalTime, burstTime, priority);

    if (this->size == 0) {
        node->next = nullptr;
        node->prev = nullptr;
        this->head = node;
        this->tail = node;
    } else if (this->head->priority >= node->priority) {
        node->next = this->head;
        this->head->prev = node;
        this->head = node;
    } else {
        Node<T> *iterator = new Node<T>();
        iterator = this->head;
        while (iterator != nullptr) {
            if (iterator->next == nullptr) {
                this->tail = node;
                iterator->next = node;
                node->prev = iterator;
                break;
            } else if (iterator->next->priority >= node->priority) {
                iterator->next->prev = node;
                node->next = iterator->next;
                iterator->next = node;
                node->prev = iterator;
                break;
            }
            iterator = iterator->next;
        }
    }

    this->size++;
}

template <typename T>
void DoubleLinkedList<T>::deleteNode(int pid) {
    if(this->head->pid == pid) {
        this->head->next->prev = nullptr;
        this->head = this->head->next;
    } else if(this->tail->pid == pid) {
        this->tail->prev->next = nullptr;
        this->tail = this->tail->prev;
    } else {
        Node<T>* iterator = new Node<T>();
        iterator = this->head;

        while(iterator != nullptr) {
            if(iterator->pid == pid) {
                iterator->prev->next = iterator->next;
                iterator->next->prev = iterator->prev;
            }
            iterator = iterator->next;
        }
    }
    this->size--;
}

template <typename T>
bool DoubleLinkedList<T>::isElement(T x) {
    Node<T> *iterator;

    iterator = this->head;
    //initializes i to the head

    while (iterator != nullptr) {
        if (iterator->pid == x) {
            return true;
        }  //returns true if data is an element of the list
        iterator = iterator->next;
    }

    return false;
}

template <typename T>
Node<T>* DoubleLinkedList<T>::getElement(int x) {
    Node<T> *iterator;

    iterator = this->head;

    while(iterator != nullptr) {
        if(iterator->pid = x) {
            return iterator;
        }
        iterator = iterator->next;
    }

    cout << "Element not found" << endl;
}

template <typename T>
void DoubleLinkedList<T>::print() {
    if(this->size == 0) {
        cout << "The list is empty!" << endl;
    } else {
        Node<T>* iterator = new Node<T>();
        iterator = this->head;

        cout << "nullptr <--> ";
        while(iterator != nullptr) {
            cout << iterator->pid << "," << iterator->priority << " <--> ";
            iterator = iterator->next;
        }
        cout << "nullptr" << endl;
    }
}

template<typename T>
Node<T> *DoubleLinkedList<T>::getHead() {
    return head;
}

template<typename T>
Node<T> *DoubleLinkedList<T>::getTail() {
    return this->head;
}

template<typename T>
int DoubleLinkedList<T>::getSize() {
    return this->size;
}

#endif
