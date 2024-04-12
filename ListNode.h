#ifndef LISTNODE_H
#define LISTNODE_H
#include <iostream>
#include <exception>

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

#endif