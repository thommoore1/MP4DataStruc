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

                    /* 
                        - gets time values by finding the next empty char and getting all values up to that
                        - then substrings to remove the values we already have
                    */
                    int empty1 = lineData.find(' ');
                    int time1 = stoi(lineData.substr(0, empty1));
                    lineData = lineData.substr(empty1 + 1, lineData.size() - empty1);

                    int empty2 = lineData.find(' ');
                    int time2 = stoi(lineData.substr(0, empty2));
                    lineData = lineData.substr(empty2 + 1, lineData.size() - empty2);

                    int empty3 = lineData.find(' ');
                    int time3 = stoi(lineData.substr(0, empty3));
                    lineData = lineData.substr(empty3 + 1, lineData.size() - empty3);

                    // gets offices from remaining line data
                    char office1 = lineData[0];
                    char office2 = lineData[2];
                    char office3 = lineData[4];

                    // make new student and add to queue
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


    //TODO: proper comment
    registrar->makeQueuePrepArray(studentCount);
    finAid->makeQueuePrepArray(studentCount);
    cashier->makeQueuePrepArray(studentCount);

    stuArray = new Customer*[studentCount]; //adding student queue to student array
    int index = -1;

    while(!(studentQueue->isEmpty())){
        stuArray[++index] = studentQueue->remove();
    }

    delete studentQueue;
    
    time = 1;
    int stuJoinIndex = 0;
    int studentmax;
    int newStudentMax = 0;
    int currentStudentNum = 0;


    while(studentsNotDone()){
        if(!(joinTimeQueue->isEmpty()) && time == joinTimeQueue->peek()){//time is equal to next student join time
            joinTimeQueue->remove();
            stuJoinIndex = newStudentMax;
            studentmax = numOfStudentsQueue->remove();

            //TODO: proper comment
            for(int i = stuJoinIndex; i < (stuJoinIndex + studentmax); ++i){
                ++currentStudentNum;
                if(stuArray[i]->getNextOffice() == 'F'){
                    finAid->addStudentToQueue(stuArray[i]);
                }
                else if(stuArray[i]->getNextOffice() == 'R'){
                    registrar->addStudentToQueue(stuArray[i]);
                }
                else if(stuArray[i]->getNextOffice() == 'C'){
                    cashier->addStudentToQueue(stuArray[i]);
                }
                newStudentMax = i + 1;
            }
        }

        // increment time for all offices
        ++time;
        finAid->timeIncrement();
        registrar->timeIncrement();
        cashier->timeIncrement();

        for(int i = 0; i < currentStudentNum; ++i){ //moving students to new offices if done
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

        // goes back and adds queues from other offices
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

    cout << "Cashier's Office:" << endl;
    cout << "Mean student wait time: " << to_string(cashier->getMeanWaitTime()) << " tick(s)" << endl;
    cout << "Mean window idle time: " << to_string(cashier->getMeanIdleTime()) << " ticks(s)" << endl;
    cout << "Longest student wait time: " << cashier->getLongestWaitTime() << " ticks(s)" << endl;
    cout << "Longest window idle time: " << cashier->getLongestIdleTime() << " ticks(s)" << endl << endl;

    cout << "Financial Aid Office:" << endl;
    cout << "Mean student wait time: " << to_string(finAid->getMeanWaitTime()) << " ticks(s)" << endl;
    cout << "Mean window idle time: " << to_string(finAid->getMeanIdleTime()) << " ticks(s)" << endl;
    cout << "Longest student wait time: " << finAid->getLongestWaitTime() << " ticks(s)" << endl;
    cout << "Longest window idle time: " << finAid->getLongestIdleTime() << " ticks(s)" << endl << endl;

    cout << "Registrar's Office" << endl;
    cout << "Mean student wait time: " << to_string(registrar->getMeanWaitTime()) << " ticks(s)" << endl;
    cout << "Mean window idle time: " << to_string(registrar->getMeanIdleTime()) << " ticks(s)" << endl;
    cout << "Longest student wait time: " << registrar->getLongestWaitTime() << " ticks(s)" << endl;
    cout << "Longest window idle time: " << registrar->getLongestIdleTime() << " ticks(s)" << endl << endl;

    int numOfStudents = cashier->getVisitsOver10();
    numOfStudents += finAid->getVisitsOver10();
    numOfStudents += registrar->getVisitsOver10();

    cout << "Number of students waiting over 10 minutes across all offices: " << numOfStudents << " tick(s)" << endl;

    int fiveMinWindow = cashier->getTotalIdleOver5();
    fiveMinWindow += registrar->getTotalIdleOver5();
    fiveMinWindow += finAid->getTotalIdleOver5();

    cout << "Number of windows idle for over 5 minutes across all offices: " << fiveMinWindow << " tick(s)" << endl;
}

bool ServiceCenter::studentsNotDone(){
    // checks to see if not all students are done
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