#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>

using namespace std;

class Customer{
    public:
        Customer();
        Customer(int timeAtOfficeA, int timeAtOfficeB, int timeAtOfficeC, char officeA, char officeB, char officeC);
        ~Customer();
        Customer(Customer* c);

        char getNextOffice();
        bool needsNewQueue();
        bool notDone();
        void setCurrentQueue(char newQueue);
        void timeIncrement();
        void enterQueue(int enterTime);
        int exitQueue(int exitTime);

    private:
        int testVariable; //TODO: delete later

        int timeWaited;
        int initialQueueTime;
        int officeNum;
        int* officeTimes;
        char* officeOrder;
        char currentQueue;
};

#endif