#ifndef SERVICECENTER_H
#define SERVICECENTER_H

#include <iostream>
#include <exception>
#include <fstream>
#include <string>

#include "Queue.h"
#include "Office.h"
#include "Customer.h"

using namespace std;

class ServiceCenter{
    public:
        ServiceCenter(string fileName);
        ServiceCenter();
        ~ServiceCenter();

    private:
        bool studentsNotDone();
        void printFinalData();
        unsigned int time;
        unsigned int studentCount;
        Office* registrarSim;
        Office* cashierSim;
        Office* finAidSim;

        char timeOrStudentNum;
        Queue<int>* numOfStudentsQueue;
        Queue<int>* joinTimeQueue;
        Queue<Customer*>* studentQueue;

        Office* registrar;
        Office* cashier;
        Office* finAid;
        Customer** stuArray;
};


#endif