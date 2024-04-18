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

double Office::getMeanIdleTime() { // gets the mean idle time from all windows' total idle times
    int totalIdleTime = 0;
    for (int i = 0; i < numWindows; ++i) {
        // add idle time of window to total
        totalIdleTime += windows[i]->getTotalIdleTime();
    }
    return ((double) totalIdleTime / (double) numWindows);
}

int Office::getLongestIdleTime() { // gets the longest idle time amongst all windows
    int maxIdleTime = 0;
    for (int i = 0; i < numWindows; ++i) {
        // if the max idle time is greater, replace the old one
        int currIdleTime = windows[i]->getTotalIdleTime();
        if (currIdleTime > maxIdleTime) maxIdleTime = currIdleTime;
    }
    return maxIdleTime;
}

int Office::getTotalIdleOver5() { // returns the total number of windows with idles over 5
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

void Office::prepStudentForQueue(Customer *c){ //adds student to the array and increases index. This method is only called for students who are moving from another office to this current office
    queuePrep[queuePrepIndex] = c;
    ++queuePrepIndex;
}

void Office::makeQueuePrepArray(int sn){ //makes an array based on number of students
    queuePrep = new Customer*[sn];
    queuePrepIndex = 0;
}
 
void Office::addQueueFromOtherOffice(){ //This method is for when a student finishes and needs to be added to another queue when coming from another.
    for(int i = 0; i < queuePrepIndex; ++i){
        if(queuePrep[i] == NULL){
            break;
        }
        addStudentToQueue(queuePrep[i]);
    }

    for(int i = 0; i < queuePrepIndex; ++i){
        if(queuePrep[i] == NULL){
            break;
        }
        queuePrep[i] == NULL;
    }
    queuePrepIndex = 0;
}