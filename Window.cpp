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
    /*TODO: Implement time incrementation
        - check if customer exists
            - if so, check if they're done or not
        - if no customer, update idle times as necessary
    */
}

bool Window::isEmpty() {
    return (currentCustomer == NULL);
}

bool Window::isCustomerDone() {
    //TODO: check if customer is done. if necessary, implement sending them back somehow
    return false;
}

int Window::getLongestIdleTime() {
    return longestIdleTime;
}

int Window::getNumIdlesOver5() {
    return idlesOver5;
}

int Window::getTotalIdleTime() {
    return totalIdleTime;
}