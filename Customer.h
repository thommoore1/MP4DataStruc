#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>

using namespace std;

class Customer{
    public:
        Customer();
        Customer(int timeAtOfficeA, int timeAtOfficeB, int timeAtOfficeC, char officeA, char officeB, char officeC);
        ~Customer();

        char getNextOffice();
        bool needsNewQueue();
        bool notDone();
        void setCurrentQueue(char newQueue);
        void timeIncrement();

    private:
        int officeNum;
        int* officeTimes;
        char* officeOrder;
        char currentQueue;
};

#endif;