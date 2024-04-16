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

        cout << " THIS IS TOM: " << currentOffice << endl;

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
        cout << "Hello this is a test: " << officeNum << endl;
        return (officeNum < 3);
    }

    void Customer::setCurrentOffice(char newQueue){
        currentOffice = newQueue;
    }

    void Customer::timeIncrement(){
        cout << "student time increment. YES" << endl;
        cout << "Current Office Num: " << officeNum << endl;
        cout << currentOffice << endl;
        cout << "is this the problem" << endl;

        ++timeWaited;

        if(officeNum < 3){
            cout << "Time waited: " << timeWaited << " and office Time: " << officeTimes[officeNum] << endl;
            if(timeWaited == officeTimes[officeNum]){
                cout << "office num not the problem" << endl;
                ++officeNum;
                timeWaited = 0;
                currentOffice = 'N';
            }
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