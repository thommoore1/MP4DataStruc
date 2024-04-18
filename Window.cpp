#include "Window.h"

Window::Window(string deleteThisLater) {

    currentTime = 0;
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
    currentTime++;
    // increment time of customer
    if(currentCustomer != NULL){
        cout << "Has a customer " << currentCustomer << " at time " << currentTime << endl;
        currentCustomer->timeIncrement();
        // check if done
        if (currentCustomer->needsNewQueue()){
            currentCustomer = NULL;
        }
    }
    else {
        cout << "Idle for " << currentIdle << " at time " << currentTime << endl;
        // iterate idle time if no customer
        currentIdle++;
        totalIdleTime++;

        // update idle trackers based on time spent
        if (currentIdle == 5) idlesOver5++;
        if (currentIdle > longestIdleTime) 
            longestIdleTime = currentIdle;
    }
}

void Window::approachWindow(Customer* c) {
    currentCustomer = c;
    currentIdle = 0;
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