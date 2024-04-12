#ifndef WINDOW_H
#define WINDOW_H

#include "Customer.h"
#include <iostream>
using namespace std;

class Window {

    public:
        Window();
        ~Window();

        void timeIncrement();

        bool isEmpty();
        void approachWindow(Customer c);
        Customer *currentCustomer;

    private:
        // time tracking variables
        int longestIdletime;
        int idleOver5;
        int totalIdle;


};


#endif