#ifndef SERVICECENTER_H
#define SERVICECENTER_H

#include <iostream>
#include <exception>
#include <fstream>
#include "Queue.h"
#include "Student.h"

using namespace std;

class ServiceCenter{
    public:
        ServiceCenter(string fileName);
        ~ServiceCenter();

    private:
        unsigned int time;
        Office* registrarSim;
        Office* cashierSim;
        Office* finAidSim;
};


#endif;