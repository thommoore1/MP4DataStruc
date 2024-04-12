#ifndef SERVICECENTER_H
#define SERVICECENTER_H

#include <iostream>
#include <exception>
#include <fstream>

using namespace std;

class ServiceCenter{
    public:
        ServiceCenter(string fileName);

    private:
        unsigned int time;
        registrar* registrarSim;
        cashier* cashierSim;
        finAid* finAidSim;
};


#endif;