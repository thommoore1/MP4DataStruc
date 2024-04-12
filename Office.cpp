#include "Office.h"

Office::Office(char name, int numWindows) {
    queue = new Queue<Customer>;
    windows = new Window[numWindows];
    // create new windows for length of windows
    for (int i = 0; i < numWindows; ++i) {
        Window *w = new Window();
        windows[i] = w;
    }
    officeName = name;
    this.numWindows = numWindows

    // set all aux variables to 0
    totalWaitTime = 0;
    totalVisitors = 0;
    longestWaitTime = 0;
    visitsOver10 = 0;
    timeCounter = 0;
}

Office::~Office() {
    delete queue;
    delete[] windows;
}

void Office::timeIncrement() {

    /* TODO:
        - Add students to queue
        - Increment time for windows
        - Check if any windows are open after using firstEmptyWindow()
            - sendStudentToWindow()
            - keep iterating until either -1 response or empty queue
        - addToWaitTime()
    */

}

void Office::addStudentToQueue(Student* s) {
    queue->insert(s);
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
    return (totalWaitTime / totalVisitors);
}

int Office::getLongestWaitTime() {
    return longestWaitTime;
}

int Office::getVisitsOver10() {
    return visitsOver10;
}

int Office::getMeanIdleTime() {
    int totalIdleTime = 0;
    for (int i = 0; i < numWindows; ++i) {
        // add idle time of window to total
        totalidleTime += windows[i]->getIdleTime();
    }
    return (totalIdleTime / numWindows);
}

int Office::getLongestIdleTime() {-
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
        if (windows[i]->isEmpty()) return i;
    }

    return -1;
}

void Office::sendStudentToWindow(int windowNum) {
    // removes a student from the queue and sends them to the first available window
    windows[i]->approachWindow(queue->remove());
}

void Office::addToWaitTime() {
    // get number of students in the array
    // ex: if there are 3 students in line and 1 time has passed, then a total of 3 wait time has happened
    totalWaitTime += queue->getSize();
}

void Office::prepStudentForQueue(Student* s){
    queuePrep[queuePrepIndex] = s;
    ++queuePrepIndex;
}

void Office::makeQueuePrepArray(int sn){
    queuePrep = new int[sn];
    queuePrepIndex = 0;
}



void Office::addQueueFromOtherOffice(){
    for(int i = 0; i < queuePrepIndex; ++i){
        if(queuePrep == NULL){
            break;
        }
        if(queuePrep[i]->getNextOffice() == 'C' && officeName != 'C'){
            addStudentToQueue(queuePrep[i]);
        }
    }
    for(int i = 0; i < queuePrepIndex; ++i){
        if(queuePrep == NULL){
            break;
        }
        if(queuePrep[i]->getNextOffice() == 'F' && officeName != 'F'){
            addStudentToQueue(queuePrep[i]);
        }
    }
    for(int i = 0; i < queuePrepIndex; ++i){
        if(queuePrep == NULL){
            break;
        }
        if(queuePrep[i]->getNextOffice() == 'R' && officeName != 'R'){
            addStudentToQueue(queuePrep[i]);
        }
    }

    for(int i = 0; i < queuPrepIndex; ++i){
        if(queuePrep[i] == NULL){
            break;
        }
        queuePrep[i] == NULL;
    }
}