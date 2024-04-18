#include "Customer.h"

Customer::Customer(){}

Customer::Customer(int timeAtOfficeA, int timeAtOfficeB, int timeAtOfficeC, char officeA, char officeB, char officeC){
    timeWaited = 0;
    initialQueueTime = 0;
    currentOffice = 'N';
    previousOffice = 'N';
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
    delete[] officeTimes;
    delete[] officeOrder;
}

char Customer::getNextOffice(){ // gets the next office char
    return officeOrder[officeNum];
}

bool Customer::needsNewQueue(){ // tells if student needs to be put to a new queue
    return (currentOffice == 'N');
}

bool Customer::notDone(){ // checks if customer is not done with everything
    return (officeNum < 3);
}

void Customer::setCurrentOffice(char newQueue){ // updates the char of the current office
    currentOffice = newQueue;
}

void Customer::timeIncrement(){

    // iterates through all offices and iterates officeNum if the time is at 0
    for(int i = 0; i < 3; ++i){
        if(officeNum < 3 && officeTimes[officeNum] == 0){
            ++officeNum;
        }
    }

    // iterates time waited
    ++timeWaited;
    if(officeNum < 3){
        // checks if student is done with this specific office
        if(timeWaited == officeTimes[officeNum]){
            ++officeNum;
            timeWaited = 0;
            previousOffice = currentOffice;
            currentOffice = 'N';

            // check if student is not supposed to spend any time here
            while(nextOfficeIsZero()){ //If the student is not spending any time at their next office, move them to the next one, until they are finished
                zeroMove();

                if(!(notDone())){
                    break;
                }
                
            }
        }
    }
}

/*
    enter and exit queues are used to keep track of customer's wait times in the queue for an office
*/
void Customer::enterQueue(int enterTime) {
    initialQueueTime = enterTime;
}

int Customer::exitQueue(int exitTime) {
    return (exitTime - initialQueueTime);
}

bool Customer::nextOfficeIsZero(){ // checks if the next office has a 0 time value
    return(officeTimes[officeNum] == 0);
}

void Customer::zeroMove(){ // adjustment function for if the nextOfficeIsZero() is true
    ++officeNum;
}

char Customer::getPrevOffice(){
    return previousOffice;
}