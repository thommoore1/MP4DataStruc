#include "Window.h"

Window::Window() {
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
        // check if done
        if (currentCustomer->needsNewQueue()){
            currentCustomer = NULL;
        }
    }
    else {
        // iterate idle time if no customer
        currentIdle++;
        totalIdleTime++;

        // update idle trackers based on time spent
        if (currentIdle == 5) idlesOver5++;
        if (currentIdle > longestIdleTime) 
            longestIdleTime = currentIdle;
    }
}

// updates customer at window and idle time
void Window::approachWindow(Customer* c) {
    currentCustomer = c;
    currentIdle = 0;
}

// aux empty function
bool Window::isEmpty() {
    return (currentCustomer == NULL);
}


/* accessors */
int Window::getLongestIdleTime() {
    return longestIdleTime;
}

int Window::getNumIdlesOver5() {
    return idlesOver5;
}

int Window::getTotalIdleTime() {
    return totalIdleTime;
}