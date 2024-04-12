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
        ~ServiceCenter();

    private:
        bool StudentsNotDone();
        unsigned int time;
        Office* registrarSim;
        Office* cashierSim;
        Office* finAidSim;

        char timeOrStudentNum;
        Queue<int>* numOfStudentsQueue;
        Queue<int>* joinTimeQueue;
        Queue<Customer>* studentQueue;

        Office* registrar;
        Office* cashier;
        Office* finAid;
};


#endif;