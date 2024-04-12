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
        bool isCustomerDone();

        // private var accessors
        int getLongestIdleTime();
        int getNumIdlesOver5();
        int getTotalIdleTime();

    private:
        // time tracking variables
        int longestIdleTime;
        int idlesOver5;
        int currentIdle;
        int totalIdleTime;
        Customer* currentCustomer;

};


#endif