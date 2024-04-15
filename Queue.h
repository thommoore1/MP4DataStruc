#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <exception>
#include "DblList.h"

using namespace std;

template <typename T>
class Queue{
    public:
        Queue();
        ~Queue();
        void insert(T d); //enqueue
        T remove(); //dequeue

        //aux functions
        T peek();
        bool isEmpty();
        unsigned int getSize();
    private:
        DblList<T> *myQueue;
};

template <typename T>
Queue<T>::Queue(){
    myQueue = new DblList<T>();
}

template <typename T>
Queue<T>::~Queue(){
    delete myQueue;
}

template <typename T>
void Queue<T>::insert(T d){
    cout << "yep" << endl;
    myQueue->insertBack(d);
    cout << "hello" << endl;
}

template <typename T>
T Queue<T>::remove(){
    if(isEmpty()){
        throw runtime_error("queue is empty, nothing to remove");
    }
    return myQueue->removeFront();
}

template <typename T>
T Queue<T>::peek(){
    return myQueue->getFront();
}

template <typename T>
bool Queue<T>::isEmpty(){
    return myQueue->isEmpty();
}

template <typename T>
unsigned int Queue<T>::getSize(){
    return myQueue->getSize();
}

#endif