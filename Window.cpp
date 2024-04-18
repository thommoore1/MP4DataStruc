#include "Window.h"

Window::Window(string deleteThisLater) {
    alsoDeleteThis = deleteThisLater; 

    longestIdleTime = 0;
    idlesOver5 = 0;
    totalIdleTime = 0;
    currentIdle = 0;
    currentCustomer = NULL;
}

Window::~Window() {
    currentCustomer = NULL;
}

void Window::timeIncrement() {
    // increment time of customer
    if(currentCustomer != NULL){
        currentCustomer->timeIncrement();
    }
    if (currentCustomer) { // if there is a customer
        // check if done
        if (currentCustomer->needsNewQueue()){
            currentCustomer = NULL;
        }
    }
    else {
        // iterate idle time if no customer
        totalIdleTime++;
        currentIdle++;

        // update idle trackers based on time spent
        if (currentIdle == 5) idlesOver5++;
        if (currentIdle > longestIdleTime) 
            longestIdleTime = currentIdle;
    }
}

void Window::approachWindow(Customer* c) {
    currentIdle = 0;
    currentCustomer = c;
    //currentCustomer->setOffice();
}

bool Window::isEmpty() {
    return (currentCustomer == NULL);
}

// bool Window::isCustomerDone() {
//     //TODO: check if customer is done. if necessary, implement sending them back somehow
//     return false;
// }

int Window::getLongestIdleTime() {
    return longestIdleTime;
}

int Window::getNumIdlesOver5() {
    return idlesOver5;
}

int Window::getTotalIdleTime() {
    return totalIdleTime;
}