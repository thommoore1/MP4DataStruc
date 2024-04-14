#include "ServiceCenter.h"

ServiceCenter::ServiceCenter(string fileName){
    cout << "GAMER" << endl;

    string line;
    int count = -1;
    int count2 = -1;
    ifstream readFile(fileName);
    timeOrStudentNum = 't';

    numOfStudentsQueue = new Queue<int>();
    joinTimeQueue = new Queue<int>(); // This is a queue for times when students join. NOT joining a Timequeue.   Queue<int>* studentNum = new Queue<int>();
    studentQueue = new Queue<Customer*>();
    
    studentCount = 0;

    cout << "Ashs" << endl;

    if(readFile.is_open()){
        while(getline(readFile,line)){
            cout << "TOm" << endl;
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
                    cout << "yippie" << endl;
                    string lineData = line;

                    int time1 = stoi(lineData.substr(0, lineData.find(' ')));
                    lineData = line.substr(lineData.find(' ') + 1, lineData.size());

                    cout << "YUH" << endl;

                    int time2 = stoi(lineData.substr(0, lineData.find(' ')));
                    lineData = line.substr(lineData.find(' ') + 1, lineData.size());

                    cout << "YOUM" << endl;

                    int time3 = stoi(lineData.substr(0, lineData.find(' ')));
                    lineData = line.substr(lineData.find(' ') + 1, lineData.size());

                    cout << "argh" << endl;

                    char office1 = lineData[0];
                    char office2 = lineData[2];
                    char office3 = lineData[4];

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
        stuArray[++index] = studentQueue->remove();
    }

    delete studentQueue;
    
    time = 1;
    int stuJoinIndex = 0;

    while(studentsNotDone()){
        if(time == joinTimeQueue->peek()){//time is equal to next student join time
            joinTimeQueue->remove();
            for(int i = stuJoinIndex; i < (i + numOfStudentsQueue->remove()); ++i){
                if(stuArray[i]->getNextOffice() == 'F'){
                    finAid->addStudentToQueue(stuArray[i]);
                }
                else if(stuArray[i]->getNextOffice() == 'R'){
                    registrar->addStudentToQueue(stuArray[i]);
                }
                else if(stuArray[i]->getNextOffice() == 'C'){
                    cashier->addStudentToQueue(stuArray[i]);
                }
                stuJoinIndex = i;
            }
        }

        ++time;
        finAid->timeIncrement();
        registrar->timeIncrement();
        cashier->timeIncrement();

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

    //print stuff
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