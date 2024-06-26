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
        void setCurrentOffice(char newQueue);
        void timeIncrement();
        void enterQueue(int enterTime);
        int exitQueue(int exitTime);
        bool nextOfficeIsZero();
        void zeroMove();
        char getPrevOffice();

    private:
        int timeWaited;
        int initialQueueTime;
        int officeNum;
        int* officeTimes;
        char* officeOrder;
        char currentOffice;
        char previousOffice;
};

#endif