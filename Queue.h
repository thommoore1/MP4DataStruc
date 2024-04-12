#ifndef GENQUEUE_H
#define GENQUEUE_H

#include <iostream>
#include <exception>
#include "DblList.h"

using namespace std;

template <typename T>
class GenQueue{
    public:
        GenQueue();
        ~GenQueue();
        void insert(T d); //enqueue
        T remove(); //dequeue

        //aux functions
        T peek();
        bool isEmpty();
        unsigned int getSize();
    private:
        LinkedList *myQueue;
};

template <typename T>
GenQueue<T>::GenQueue(){
    myQueue = new LinkedList<T>();
}

template <typename T>
GenQueue<T>::~GenQueue(){
    delete myQueue;
}

template <typename T>
void GenQueue<T>::insert(T d){
    myQueue->insertBack(d);
}

template <typename T>
T GenQueue<T>::remove(){
    if(isEmpty()){
        throw runtime_error("queue is empty, nothing to remove");
    }
    return myQueue->removeFront();
}

template <typename T>
T GenQueue<T>::peek(){
    return myQueue->getFront();
}

template <typename T>
bool GenQueue<T>::isEmpty(){
    return myQueue->isEmpty();
}

template <typename T>
unsigned int GenQueue<T>::getSize(){
    return myQueue->getSize();
}

#endif