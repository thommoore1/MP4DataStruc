#ifndef OFFICE_H
#define OFFICE_H

#include "Window.h"
#include "Customer.h"

#include <iostream>
using namespace std;

class Office {

    public:
        Office(char officeName, int numWindows);
        ~Office();

        void timeIncrement();

        void addStudentToQueue(Customer s);
        void prepStudentForQueue(Customer s); //TODO: This method is for adding students to queue who are coming from another office. Just adds them to an array that will be used by addQueueFromOtherOffice()
        void addQueueFromOtherOffice(); //TODO: This method should add students to queue depending on which office they are coming from
        void makeQueuePrepArray(int sn);

        // accessors for private vars
        int getNumWindows();
        int getTotalWaitTime();
        int getTotalVisitors();
        double getMeanWaitTime();
        int getLongestWaitTime();
        int getVisitsOver10();

        // get total idle time
        int getMeanIdleTime();
        int getLongestIdleTime();
        int getTotalIdleOver5();


    private:

        Customer* queuePrep; //TODO: constructor
        int stuNum;
        int queuePrepIndex;
        int studentsToMove;

        int timeCounter; 

        Queue<Customer> *queue;
        Window* windows;
        char officeName;
        int numWindows;
        int* prepQueue();

        // aux methods for time increment
        int firstEmptyWindow();
        void sendStudentToWindow(int windowNum);
        void addToWaitTime();

        // used for the mean wait time
        int totalWaitTime;
        int totalVisitors;

        int longestWaitTime;
        int visitsOver10;   

        /*
        At the end of the simulation, your program will display (on standard out) the following (labeled)
            metrics:
            1. The mean student wait time for each office.
            2. The longest student wait time for each office.
            3. The number of students waiting over 10 minutes total across all offices.
            4. The mean window idle time for each office
            5. The longest window idle time for each office
            6. Number of windows idle for over 5 minutes across all offices.
        */

};


#endif