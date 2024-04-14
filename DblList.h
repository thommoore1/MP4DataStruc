#ifndef DBLLIST_H
#define DBLLIST_H

#include <iostream>
using namespace std;

template <typename T>
class ListNode{
    public:
        ListNode();
        ListNode(T d);
        ~ListNode();
        ListNode *next;
        ListNode *prev;
        T data;
};

template <typename T>
ListNode<T>::ListNode(){}

template <typename T>
ListNode<T>::ListNode(T d){
    data = d;
    next = NULL;
    prev = NULL;
}

template <typename T>
ListNode<T>::~ListNode(){
    next = NULL;
    prev = NULL;
}




template <typename T>
class DblList{
    private:
        ListNode<T> *front;
        ListNode<T> *back;
        unsigned int size;
    public:
        DblList();
        ~DblList();

        void insertFront(T d);
        void insertBack(T d);
        T removeFront();
        T removeBack();
        T removeNode(T value); //method for removing node not the front or the back
        int find(T value); //this is identical to search/find in a SingleLinkedList
        bool isEmpty();
        unsigned int getSize();
        T getFront();
};

template <typename T>
bool DblList<T>::isEmpty() {
    return (size == 0);
}

template <typename T>
DblList<T>::DblList(){
    front = NULL;
    back = NULL;
    size = 0;
}

template <typename T>
DblList<T>::~DblList(){
    while(!isEmpty()){
        removeFront();
    }
}

template <typename T>
T DblList<T>::getFront(){
    if(size == 0){
        throw runtime_error("list is empty");
    }
    return front->data;
}

template <typename T>
void DblList<T>::insertFront(T d){
    ListNode<T> *node = new ListNode<T>(d);

    if(isEmpty()){
        back = node;
    }
    else{
        node->next = front;
        front->prev = node;
    }
    front = node;
    ++size;
}

template <typename T>
void DblList<T>::insertBack(T d){
    ListNode<T> *node = new ListNode<T>(d);

    if(isEmpty()){
        front = node;
    }
    else {
        node->prev = back;
        back->next = node;
    }
    back = node;
    ++size;
}

template <typename T>
T DblList<T>::removeFront(){
    if(isEmpty()){
        throw runtime_error("list is empty");
    }

    ListNode<T> *temp = front;

    if(front->next == NULL){
        back = NULL;
    }
    else{
        front->next->prev = NULL;
    }

    front = front->next;
    temp->next = NULL;
    T data = temp->data;
    --size;
    delete temp;

    return data;

}

template <typename T>
T DblList<T>::removeBack(){
    if(isEmpty()){
        throw runtime_error("list is empty");
    }

    ListNode<T> *temp = back;

    if(back->prev == NULL){
        front = NULL;
    }
    else{
        //more than one node
        back->prev->next = NULL;
    }
    back = back->prev;
    temp->prev = NULL;
    T data = temp->data;
    --size;
    delete temp;

    return data;
}

template <typename T>
int DblList<T>::find(T value){
    int pos = -1;
    ListNode<T> *curr = front;

    while(curr != NULL){
        ++pos;

        if(curr->data == value){
            break;
        }
        curr = curr->next;
    }
    if(curr == NULL){
        pos = -1;
    }
    return pos;
}

template <typename T>
T DblList<T>::removeNode(T value){
    if(isEmpty()){
        throw runtime_error("list is empty");
    }

    ListNode<T> *curr = front;
    while(curr->data != value){
        curr = curr->next;

        if(curr == NULL){
            throw runtime_error("Value not found");
        }
    }

    if(getSize() == 1){
        front = NULL;
        back = NULL;
    }
    else if(curr == front){
        front = curr->next;
        front->prev = NULL;
    }
    else if(curr == back){
        back = curr->prev;
        back->next = NULL;
    }
    else{
        //current is between front and back
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }
    curr->next = NULL;
    curr->prev = NULL;
    T temp = curr->data;
    --size;
    delete curr;
    return temp;
}

template <typename T>
unsigned int DblList<T>::getSize(){
    return size;
}

#endif