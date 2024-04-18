#include "Customer.h"

Customer::Customer(Customer* c){ //TODO: Delete
    timeWaited = c->timeWaited;
    initialQueueTime = c->initialQueueTime;
    currentOffice = c->currentOffice;
    officeNum = c->officeNum;
    officeTimes = new int[3];
    officeTimes[0] = c->officeTimes[0];
    officeTimes[1] = c->officeTimes[1];
    officeTimes[2] = c->officeTimes[2];
    officeOrder = new char[3];
    officeOrder[0] = c->officeOrder[0];
    officeOrder[1] = c->officeOrder[1];
    officeOrder[2] = c->officeOrder[2];
}

Customer::Customer(){
    currentOffice = 'N';
}

Customer::Customer(int timeAtOfficeA, int timeAtOfficeB, int timeAtOfficeC, char officeA, char officeB, char officeC){
    timeWaited = 0;
    initialQueueTime = 0;
    currentOffice = 'N';
    officeNum = 0;
    officeTimes = new int[3];
    officeTimes[0] = timeAtOfficeA;
    officeTimes[1] = timeAtOfficeB;
    officeTimes[2] = timeAtOfficeC;
    officeOrder = new char[3];
    officeOrder[0] = officeA;
    officeOrder[1] = officeB;
    officeOrder[2] = officeC;

    testVariable = timeAtOfficeA;
}

Customer::~Customer(){
    delete[] officeTimes;
    delete[] officeOrder;
}

char Customer::getNextOffice(){
    return officeOrder[officeNum];
}

bool Customer::needsNewQueue(){
    return (currentOffice == 'N');
}

bool Customer::notDone(){
    return (officeNum < 3);
}

void Customer::setCurrentOffice(char newQueue){
    currentOffice = newQueue;
}

void Customer::timeIncrement(){


    for(int i = 0; i < 3; ++i){
        if(officeNum < 3 && officeTimes[officeNum] == 0){
            ++officeNum;
        }
    }


    ++timeWaited;
    if(officeNum < 3){
        if(timeWaited == officeTimes[officeNum]){
            ++officeNum;
            timeWaited = 0;
            currentOffice = 'N';

            // check if student is not supposed to spend any time here
            while(nextOfficeIsZero()){
                zeroMove();

                if(!(notDone())){
                    cout << "THIS SHOULD HAPPEN ONCE" << endl;
                    break;
                }
                
            }
        }
    }
}

void Customer::enterQueue(int enterTime) {
    initialQueueTime = enterTime;
}

int Customer::exitQueue(int exitTime) {
    return (exitTime - initialQueueTime);
}

bool Customer::nextOfficeIsZero(){
    return(officeTimes[officeNum] == 0);
}

void Customer::zeroMove(){
    ++officeNum;
}