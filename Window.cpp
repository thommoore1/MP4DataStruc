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
    cout << "window time increment " << endl;
    // increment time of customer
    if(currentCustomer){
        currentCustomer->timeIncrement();
    }
    cout << "current customer worked" << endl;    
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
    cout << "ello" << endl;
}

void Window::approachWindow(Customer* c) {
    cout << "arrrr" << endl;
    cout << "APPROACH WINDOW CURRENT C: " << c;
    currentIdle = 0;
    currentCustomer = c;
}

bool Window::isEmpty() {
    currentCustomer = new Customer();
    cout << "WINDOW CURRENT CUSTOMER: " << currentCustomer << endl;
    delete currentCustomer;
    currentCustomer = NULL;
    cout << alsoDeleteThis << endl;
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