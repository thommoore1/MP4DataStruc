#include "Customer.h"

Customer::Customer(){

}

Customer::Customer(int timeAtOfficeA, int timeAtOfficeB, int timeAtOfficeC, char officeA, char officeB, char officeC){
    currentQueue = 'N';
    officeNum = 0;
    officeTimes = new int[3];
    officeTimes[0] = timeAtOfficeA;
    officeTimes[1] = timeAtOfficeB;
    officeTimes[2] = timeAtOfficeC;
    officeOrder = new char[3];
    officeOrder[0] = officeA;
    officeOrder[1] = officeB;
    officeOrder[2] = officeC;
}

Customer::~Customer(){
    delete officeTimes;
    delete officeOrder;
}

char Customer::getNextOffice(){
    return officeOrder[officeNum];
}

bool Customer::needsNewQueue(){
    return (currentQueue == 'n');
}

bool Customer::notDone(){
    return (officeNum == 4);
}

void Customer::setCurrentQueue(char newQueue){
    currentQueue = newQueue;
}