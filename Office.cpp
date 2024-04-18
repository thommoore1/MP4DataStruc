#include "Office.h"

Office::Office(char name, int numWindows) {
    deleteThisToo = 0;

    queue = new Queue<Customer*>();
    windows = new Window*[numWindows];
    // create new windows for length of windows
    for (int i = 0; i < numWindows; ++i) {
        Window *w = new Window("this worked");
        windows[i] = w;
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
    ++timeCounter;

    // check if any windows are open
    int openWindow = firstEmptyWindow();

    while ((openWindow != -1) && (!(queue->isEmpty()))) {
        // send the student to an open window
        sendStudentToWindow(openWindow);
        // set to next variable
        openWindow = firstEmptyWindow();
    }
    for(int i = 0; i < numWindows; ++i){
        // increments window time
        windows[i]->timeIncrement();
    }
    addToWaitTime();

}

void Office::addStudentToQueue(Customer* s) {

    if(s->notDone()){
        // updates student office
        s->setCurrentOffice(officeName);
        s->enterQueue(timeCounter); 
        queue->insert(s);
        totalVisitors++;
    }
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
    // gets mean wait time by dividing total by visitors
    if(totalVisitors == 0){
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
    // removes a student from the queue and sends them to the first available window
    if(queue->peek()->exitQueue(timeCounter) > longestWaitTime){
        longestWaitTime = queue->peek()->exitQueue(timeCounter) - 1;
    }
    windows[windowNum]->approachWindow(queue->remove());
}

void Office::addToWaitTime() {
    // get number of students in the array
    // ex: if there are 3 students in line and 1 time has passed, then a total of 3 wait time has happened
    totalWaitTime += queue->getSize();
}

void Office::prepStudentForQueue(Customer *c){
    
    queuePrep[queuePrepIndex] = c;
    ++queuePrepIndex;
}

void Office::makeQueuePrepArray(int sn){
    queuePrep = new Customer*[sn];
    queuePrepIndex = 0;
}
 
void Office::addQueueFromOtherOffice(){
    for(int i = 0; i < queuePrepIndex; ++i){
        if(queuePrep[i] == NULL){
            break;
        }
        if(queuePrep[i]->getNextOffice() == 'C'){
            addStudentToQueue(queuePrep[i]);
        }
    }
    for(int i = 0; i < queuePrepIndex; ++i){
        if(queuePrep[i] == NULL){
            break;
        }
        if(queuePrep[i]->getNextOffice() == 'F'){
            addStudentToQueue(queuePrep[i]);
        }
    }
    for(int i = 0; i < queuePrepIndex; ++i){
        if(queuePrep[i] == NULL){
            break;
        }
        if(queuePrep[i]->getNextOffice() == 'R'){
            addStudentToQueue(queuePrep[i]);
        }
    }

    for(int i = 0; i < queuePrepIndex; ++i){
        if(queuePrep[i] == NULL){
            break;
        }
        queuePrep[i] == NULL;
    }
    queuePrepIndex = 0;
}