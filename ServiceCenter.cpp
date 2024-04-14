#include "ServiceCenter.h"

ServiceCenter::ServiceCenter(string fileName){
    string line;
    int count = -1;
    int count2 = -1;
    ifstream readFile(fileName);
    timeOrStudentNum = 't';

    numOfStudentsQueue = new Queue<int>();
    joinTimeQueue = new Queue<int>(); // This is a queue for times when students join. NOT joining a Timequeue.   Queue<int>* studentNum = new Queue<int>();
    studentQueue = new Queue<Customer*>();
    
    studentCount = 0;

    if(readFile.is_open()){
        while(getline(readFile,line)){
            ++count;
            if(count == 0){
                registrar = new Office('R', stoi(line));
            }
            else if(count == 1){
                cashier = new Office('C', stoi(line));
            }
            else if(count == 2){
                finAid = new Office('F', stoi(line));
            }
            else{
                if(line.size() > 1){//check if it is player data
                    string lineData = line;

                    int empty1 = lineData.find(' ');
                    int time1 = stoi(lineData.substr(0, empty1));
                    lineData = lineData.substr(empty1 + 1, lineData.size() - empty1);
                    cout << time1 << " | " << lineData << endl; 

                    int empty2 = lineData.find(' ');
                    int time2 = stoi(lineData.substr(0, empty2));
                    lineData = lineData.substr(empty2 + 1, lineData.size() - empty2);
                    cout << time2 << " | " << lineData << endl; 

                    int empty3 = lineData.find(' ');
                    int time3 = stoi(lineData.substr(0, empty3));
                    lineData = lineData.substr(empty3 + 1, lineData.size() - empty3);
                    cout << time3 << " | " << lineData << endl; 

                    char office1 = lineData[0];
                    char office2 = lineData[2];
                    char office3 = lineData[4];

                    cout << office1;
                    cout << office2;
                    cout << office3 << endl;;

                    Customer* stu = new Customer(time1, time2, time3, office1, office2, office3);
                    studentQueue->insert(stu);
                }
                else if(timeOrStudentNum == 't'){//check if is time variable
                    joinTimeQueue->insert(stoi(line));
                    timeOrStudentNum = 's';
                }
                else if(timeOrStudentNum == 's'){//check if it is num of students variable
                    studentCount += stoi(line);
                    numOfStudentsQueue->insert(stoi(line));
                    timeOrStudentNum = 't';
                }
            }
        }
    }



    registrar->makeQueuePrepArray(studentCount);
    finAid->makeQueuePrepArray(studentCount);
    cashier->makeQueuePrepArray(studentCount);

    stuArray = new Customer*[studentCount]; //adding student queue to student array
    int index = -1;
    while(!(studentQueue->isEmpty())){
        cout << "HELLO" << endl;
        stuArray[++index] = studentQueue->remove();
    }

    delete studentQueue;

    cout << "DYLAN DEV: " << endl;
    
    time = 1;
    int stuJoinIndex = 0;
    int studentmax;
    int newStudentMax = 0;

    cout << "oops" << endl;
    while(studentsNotDone()){
        cout << "I love Rene German" << endl;
        if(time == joinTimeQueue->peek()){//time is equal to next student join time
            cout << "AFDHFSDHDFSH" << endl;
            joinTimeQueue->remove();
            stuJoinIndex = newStudentMax;
            studentmax = numOfStudentsQueue->remove();
            for(int i = stuJoinIndex; i < (stuJoinIndex + studentmax); ++i){
                cout << "for loopy loop" << endl;
                cout << i << endl;
                cout << stuArray[i]->notDone() << endl;
                if(stuArray[i]->getNextOffice() == 'F'){
                    cout << "RUSSIAN" << endl;
                    finAid->addStudentToQueue(stuArray[i]);
                }
                else if(stuArray[i]->getNextOffice() == 'R'){
                    cout << "steak" << endl;
                    registrar->addStudentToQueue(stuArray[i]);
                }
                else if(stuArray[i]->getNextOffice() == 'C'){
                    cout << "lobster" << endl;
                    cashier->addStudentToQueue(stuArray[i]);
                }
                cout << "DANIEL" << endl;
                newStudentMax = i;
            }
        }

        cout << "MOORE" << endl;

        ++time;
        finAid->timeIncrement();
        registrar->timeIncrement();
        cashier->timeIncrement();

        cout << "THOMAS" << endl;

        for(int i = 0; i < studentCount; ++i){ //moving students to new offices if done
            if(stuArray[i]->needsNewQueue()){
                if(stuArray[i]->getNextOffice() == 'F'){
                    finAid->prepStudentForQueue(stuArray[i]);
                }
                else if(stuArray[i]->getNextOffice() == 'R'){
                    registrar->prepStudentForQueue(stuArray[i]);
                }
                else if(stuArray[i]->getNextOffice() == 'C'){
                    cashier->prepStudentForQueue(stuArray[i]);
                }
            }
        }

        finAid->addQueueFromOtherOffice();
        registrar->addQueueFromOtherOffice();
        cashier->addQueueFromOtherOffice();

    }

    printFinalData();

    //print stuff
}

void ServiceCenter::printFinalData(){

    // 1. The mean student wait time for each office.
    // 2. The longest student wait time for each office.
    // 3. The number of students waiting over 10 minutes total across all offices.
    // 4. The mean window idle time for each office
    // 5. The longest window idle time for each office
    // 6. Number of windows idle for over 5 minutes across all office

    cout << "---- Student Center Stats ----" << endl;

    cout << "The mean student wait time for cashier is: " << to_string(cashier->getMeanWaitTime()) << endl;
    cout << "The mean student wait time for financial aid is: " << to_string(finAid->getMeanWaitTime()) << endl;
    cout << "The mean student wait time for registrar is: " << to_string(registrar->getMeanWaitTime()) << endl;
    
    cout << "----" << endl;
    
    cout << "The longest student wait time for cashier is: " << cashier->getLongestWaitTime() << endl;
    cout << "The longest student wait time for financial aid is: " << finAid->getLongestWaitTime() << endl;
    cout << "The longest student wait time for registrar is: " << registrar->getLongestWaitTime() << endl;
    
    cout << "----" << endl;
    
    int numOfStudents = cashier->getVisitsOver10();
    numOfStudents += finAid->getVisitsOver10();
    numOfStudents += registrar->getVisitsOver10();
    cout << "The number of students waiting over 10 minutes across all offices was " << numOfStudents << endl;

    cout << "----" << endl;

    cout << "The mean window idle time for the cashier is: " << to_string(cashier->getMeanIdleTime()) << endl;
    cout << "The mean window idle time for the financial aid is: " << to_string(finAid->getMeanIdleTime()) << endl;
    cout << "The mean window idle time for the registrar is: " << to_string(registrar->getMeanIdleTime()) << endl;
    
    cout << "----" << endl;

    cout << "The longest window idle time for the cashier is: " << cashier->getLongestIdleTime() << endl;
    cout << "The longest window idle time for the financial aid is: " << finAid->getLongestIdleTime() << endl;
    cout << "The longest window idle time for the registrar is: " << registrar->getLongestIdleTime() << endl;
    
    cout << "----" << endl;

    int fiveMinWindow = cashier->getTotalIdleOver5();
    fiveMinWindow += registrar->getTotalIdleOver5();
    fiveMinWindow += finAid->getTotalIdleOver5();
    cout << "The number of windows idle for at least 5 mins across all offices is " << fiveMinWindow << endl;

    cout << "----" << endl;
}

bool ServiceCenter::studentsNotDone(){
    for(int i = 0; i < studentCount; ++i){
        if(stuArray[i]->notDone()){
            return true;
        }
    }
    return false;
}

ServiceCenter::~ServiceCenter() {
    delete numOfStudentsQueue;
    delete joinTimeQueue;
    for(int i = 0; i < studentCount; ++i){
        delete stuArray[i];
    }
    delete[] stuArray;
    delete registrar;
    delete finAid;
    delete cashier;
}