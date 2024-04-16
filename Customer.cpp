    #include "Customer.h"

    Customer::Customer(Customer* c){
        timeWaited = c->timeWaited;
        initialQueueTime = c->initialQueueTime;
        currentQueue = c->currentQueue;
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
        currentQueue = 'N';
    }

    Customer::Customer(int timeAtOfficeA, int timeAtOfficeB, int timeAtOfficeC, char officeA, char officeB, char officeC){
        timeWaited = 0;
        initialQueueTime = 0;
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

        cout << " THIS IS TOM: " << currentQueue << endl;

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
        return (currentQueue == 'N');
    }

    bool Customer::notDone(){
        cout << "Hello this is a test: " << testVariable << endl;
        return (officeNum >= 4);
    }

    void Customer::setCurrentQueue(char newQueue){
        currentQueue = newQueue;
    }

    void Customer::timeIncrement(){
        cout << "student time increment. YES" << endl;
        cout << currentQueue << endl;
        cout << "is this the problem" << endl;

        if(officeNum < 3 && timeWaited == officeTimes[officeNum]){
            cout << "office num not the problem" << endl;
            ++officeNum;
            timeWaited = 0;
            currentQueue = 'N';
        }
        cout << "yodle" << endl;
    }

    void Customer::enterQueue(int enterTime) {
        cout << "" << endl;
        initialQueueTime = enterTime;
    }

    int Customer::exitQueue(int exitTime) {
        return (exitTime - initialQueueTime);
    }