#ifndef WINDOW_H
#define WINDOW_H

#include "Student.h"
#include <iostream>
using namespace std;

class Window {

    public:
        Window();
        ~Window();

        bool isEmpty();
        void approachWindow(Student s);
        Student* student;

    private:
        // time tracking variables
        int longestIdletime;
        int idleOver5;
        int totalIdle;


};


#endif