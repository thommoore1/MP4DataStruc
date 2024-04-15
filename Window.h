#ifndef WINDOW_H
#define WINDOW_H

#include "Customer.h"
#include <iostream>
using namespace std;

class Window {

    public:
        Window(string deleteThisLater);
        ~Window();

        void timeIncrement();

        bool isEmpty();
        void approachWindow(Customer* c);

        // private var accessors
        int getLongestIdleTime();
        int getNumIdlesOver5();
        int getTotalIdleTime();

    private:
        string alsoDeleteThis;
        // time tracking variables
        int longestIdleTime;
        int idlesOver5;
        int currentIdle;
        int totalIdleTime;
        Customer* currentCustomer;

};


#endif