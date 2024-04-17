#include "Office.h"

Office::Office(char name, int numWindows) {
    deleteThisToo = 0;

    queue = new Queue<Customer*>();
    windows = new Window*[numWindows];
    // create new windows for length of windows
    cout << "NUM FREAKING WINDOWS" << numWindows << endl;
    for (int i = 0; i < numWindows; ++i) {
        cout << "yepper" << endl;
        Window *w = new Window("this worked");
        cout << "noper" << endl;
        windows[i] = w;
        cout << "WINDOWS TEST: " << windows[i]->isEmpty() << endl;
    }
    officeName = name;
    this->numWindows = numWindows;

    // set all aux variables to 0
    totalWaitTime = 0;
    totalVisitors = 0;
    longestWaitTime = 0;
    visitsOver10 = 0;
    timeCounter = 0;
}

Office::~Office() {
    delete queue;
    for(int i = 0; i < numWindows; ++i){
        delete windows[i];
    }
    delete[] windows;
}

void Office::timeIncrement() {
    cout << "time increment" << endl;
    ++timeCounter;
    cout << numWindows << endl;

    // check if any windows are open
    int openWindow = firstEmptyWindow();

    cout << "Open window index: " << openWindow << endl;
    cout << "queue is Empty value: " << queue->isEmpty() << endl;
    if(queue->isEmpty()){
        cout << "THIS IS TRUE" << endl;
    }
    else{
        cout << "false" << endl;
    }

    while ((openWindow != -1) && (!(queue->isEmpty()))) {
        cout << "SAMMY" << endl;
        cout << "IS this guy empty???: " << queue->isEmpty() << endl;
        // send the student to an open window
        sendStudentToWindow(openWindow);
        cout << "DEEP" << endl;
        // set to next variable
        openWindow = firstEmptyWindow();
        cout << "EMPTY WINDOW???: " << openWindow;
        cout << "TEEP" << endl;
    }
    for(int i = 0; i < numWindows; ++i){
        cout << i << endl;
        windows[i]->timeIncrement();
    }
    addToWaitTime();

    /* TODO:
        - Increment time for windows
        - Check if any windows are open after using firstEmptyWindow()
            - send StudentToWindow()
            - keep iterating until either -1 response or empty queue
    */
   cout << "FINISHED OFFICE TIME INC" << endl;

}

void Office::addStudentToQueue(Customer* s) {
    cout << "Student " << s <<  " added to queue" << endl;
    s->setCurrentOffice
    (officeName);
    s->enterQueue(timeCounter); 
    cout << "Keeper" << endl;
    cout << s << endl;
    cout << queue << endl;
    queue->insert(s);
    cout << "sleeper" << endl;
    totalVisitors++;
}

int Office::getNumWindows() {
    return numWindows;
}

int Office::getTotalWaitTime() {
    return totalWaitTime;
}

int Office::getTotalVisitors() {
    return totalVisitors;
}

double Office::getMeanWaitTime() {
    //totalWaitTime = 10;
    //totalVisitors = 10;
    cout << "totalWaitTime/totalVisitors: " << totalWaitTime << "/" << totalVisitors << " = ";
    if(totalWaitTime == 0){
        return 0;
    }
    return ((double) totalWaitTime / (double) totalVisitors);
}

int Office::getLongestWaitTime() {
    return longestWaitTime;
}

int Office::getVisitsOver10() {
    return visitsOver10;
}

double Office::getMeanIdleTime() {
    int totalIdleTime = 0;
    for (int i = 0; i < numWindows; ++i) {
        // add idle time of window to total
        totalIdleTime += windows[i]->getTotalIdleTime();
    }
    return ((double) totalIdleTime / (double) numWindows);
}

int Office::getLongestIdleTime() {
    int maxIdleTime = 0;
    for (int i = 0; i < numWindows; ++i) {
        // if the max idle time is greater, replace the old one
        int currIdleTime = windows[i]->getLongestIdleTime();
        if (currIdleTime > maxIdleTime) maxIdleTime = currIdleTime;
    }
    return maxIdleTime;
}

int Office::getTotalIdleOver5() {
    int counter = 0;
    for (int i = 0; i < numWindows; ++i) {
        // add idle time of window to total
        counter += windows[i]->getNumIdlesOver5();
    }
    return counter;
}


int Office::firstEmptyWindow() {
    
    /* iterate through all windows return
        - Return index of the first empty window
        - Else return -1
    */

    for (int i = 0; i < numWindows; ++i) {
        if (windows[i]->isEmpty()){
            return i;
        }
    }

    return -1;
}

void Office::sendStudentToWindow(int windowNum) {
    cout << "Rylan" << endl;
    // removes a student from the queue and sends them to the first available window
    cout << "this dude is null isnt he: " << queue->peek() << endl;
    if(queue->peek()->exitQueue(timeCounter) > longestWaitTime){
        cout << "password" << endl;
        longestWaitTime = queue->peek()->exitQueue(timeCounter) - 1;
    }

    cout << "index test: " << windowNum << endl;
    cout << "window opject exists test: " << windows[windowNum]->isEmpty() << endl;
    cout << "window location: " << windows[windowNum] << endl;
    cout << "student location: " << queue->peek() << endl;
    cout << "Student exists test: " << queue->peek()->notDone() << endl;
    

    //queue->remove();

    //Customer* testStu = new Customer(1, 1, 1, '', '', '');
    //windows[windowNum]->approachWindow(testStu);
    //delete testStu;
    //cout << "that worked bro" << endl;

    //windows[] - array of windows, printing it shows the one being accessed exists
    //windowNum - 0
    //queue->remove() - should be working

    // cout << "WHICH LOOP: " << deleteThisToo << endl;

    // if(deleteThisToo == 7){
    //     //Customer* test = new Customer(2,2,2,'','','');
    //     Customer* test2 = new Customer(queue->remove());
    //     windows[windowNum]->approachWindow(test2);
    // }
    // else{
        cout << "here we go" << endl;
    
        windows[windowNum]->approachWindow(queue->remove());
    
        cout << "there" << endl;
    //}

    //++deleteThisToo;

    
}

void Office::addToWaitTime() {
    // get number of students in the array
    // ex: if there are 3 students in line and 1 time has passed, then a total of 3 wait time has happened
    totalWaitTime += queue->getSize();
}

void Office::prepStudentForQueue(Customer *c){
    cout << "broke here" << endl;
    cout << "Customer Test: " << c->notDone() << endl;
    cout << "Queue Prep Index: " << queuePrepIndex << endl;
    queuePrep[queuePrepIndex] = c;
    cout << "queue has been prepperd" << endl;
    ++queuePrepIndex;
}

void Office::makeQueuePrepArray(int sn){
    cout << "QUEUE PREP ARRAY SIZE: " << sn << endl;
    queuePrep = new Customer*[sn];
    queuePrepIndex = 0;
}
 
void Office::addQueueFromOtherOffice(){
    cout << "Queue prep index: " << queuePrepIndex << endl;
    for(int i = 0; i < queuePrepIndex; ++i){
        cout << ")" << endl;
        if(queuePrep[i] == NULL){
            cout << "!" << endl;
            break;
        }
        cout << "next office: " << queuePrep[i]->getNextOffice() << endl;
        if(queuePrep[i]->getNextOffice() == 'C'){
            cout << "@" << endl;
            addStudentToQueue(queuePrep[i]);
        }
    }
    for(int i = 0; i < queuePrepIndex; ++i){
        cout << "(" << endl;
        if(queuePrep[i] == NULL){
            cout << "#" << endl;
            break;
        }
        if(queuePrep[i]->getNextOffice() == 'F'){
            cout << "$" << endl;
            addStudentToQueue(queuePrep[i]);
        }
    }
    for(int i = 0; i < queuePrepIndex; ++i){
        cout << "*" << endl;
        if(queuePrep[i] == NULL){
            cout << "%" << endl;
            break;
        }
        if(queuePrep[i]->getNextOffice() == 'R'){
            cout << "^" << endl;
            addStudentToQueue(queuePrep[i]);
        }
    }

    for(int i = 0; i < queuePrepIndex; ++i){
        if(queuePrep[i] == NULL){
            cout << "&" << endl;
            break;
        }
        queuePrep[i] == NULL;
    }
    queuePrepIndex = 0;
}