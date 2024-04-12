#include "ServiceCenter.h"

ServiceCenter::ServiceCenter(string fileName){
    string line;
    int count = -1;
    int count2 = -1;
    ifstream readFile(fileName);
    timeOrStudentNum = 't';

    numOfStudentsQueue = new Queue<int>();
    joinTimeQueue = new Queue<int>(); // This is a queue for times when students join. NOT joining a Timequeue.   Queue<int>* studentNum = new Queue<int>();
    studentQueue = new Queue<Customer>();
    
    int studentCount = 0;

    if(readFile.is_open()){
        while(getline(readFile,line)){
            ++count;
            if(count == 0){
                registrar = new Office('R', stoi(line)); //TODO: need to import something???
            }
            else if(count == 1){
                cashier = new Office('C', stoi(line));
            }
            else if(count == 2){
                finAid = new Office('F', stoi(line));
            }
            else{
                if(line.size() > 1){//check if it is player data
                    Customer* stu = new Customer(stoi(line[0]), stoi(line[2]), stoi(line[4]), line[6], line[8], line[10]);
                    studentQueue->add(stu);
                }
                else if(timeOrStudentNum == 't'){//check if is time variable
                    joinTimeQueue->add(stoi(line));
                    timeOrStudentNum = 's';
                }
                else if(timeOrStudentNum == 's'){//check if it is num of students variable
                    studentCount += stoi(line);
                    numOfStudentsQueue->add(stoi(line));
                    timeOrStudentNum = 't';
                }
            }
        }
    }

    registrar->makeQueuePrepArray(studentCount);
    finAid->makeQueuePrepArray(studentCount);
    cashier->makeQueuePrepArray(studentCount);

    Customer* stuArray = new Customer[studentCount]; //adding student queue to student array
    int index = -1;
    while(!(stu->isEmpty())){
        stuArray[++index] = stuArray->pop();
    }
    delete stu;
    
    time = 1;
    int stuJoinIndex = 0;

    while(studentsNotDone()){
        if(time == joinTimeQueue.peek()){//time is equal to next student join time
            joinTimeQueue.push();
            for(i = stuJoinIndex; i < (i + numOfStudentsQueue.pop()); ++i){
                if(stuArray[i]->getNextOffice() == 'F'){ //TODO: add this student method
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
            if(stuArray[i]->needsNewQueue()){ //TODO: add this student method
                if(stuArray[i]->getNextOffice() == 'F'){ //TODO: add this student method
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
        regisrar->addQueueFromOtherOffice();
        cashier->addQueueFromOtherOffice();

    }

    //print stuff
}

bool ServiceCenter::studentsNotDone(){
    for(int i = 0; i < studentCountl ++i){
        if(stuArray[i]->notDone()){
            return true;
        }
    }
    return false;
}

ServiceCenter::~ServiceCenter() {
    //TODO: destruct necessary
}