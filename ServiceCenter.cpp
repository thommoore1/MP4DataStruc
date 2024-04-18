#include "ServiceCenter.h"

ServiceCenter::ServiceCenter(string fileName){
    string line; //for file reading
    int count = -1; //for counting number of lines that have been read
    ifstream readFile(fileName); //for file reading
    if(readFile.good()){ //If the file doesn't exist, error

    timeOrStudentNum = 't'; //This variable is used after the first 3 lines (num of windows) have been read. It keeps track of if the line being read is going to be the time the students enter, or the number of students entering at that time

    numOfStudentsQueue = new Queue<int>(); // Queue for the number of students joining at one time
    joinTimeQueue = new Queue<int>(); // This is a queue for times when students join. NOT joining a Timequeue.   Queue<int>* studentNum = new Queue<int>();
    studentQueue = new Queue<Customer*>(); // This is a queue of customers
    
    studentCount = 0; //total number of students

    if(readFile.is_open()){
        while(getline(readFile,line)){
            ++count; //number of lines read
            if(count == 0){ //if it is the first line read, make registrar with that line
                registrar = new Office('R', stoi(line));
            }
            else if(count == 1){ //if it is the second line read, make cashier with that line
                cashier = new Office('C', stoi(line));
            }
            else if(count == 2){ //if it is third line, make finaid with that line
                finAid = new Office('F', stoi(line));
            }
            else{
                if(line.size() > 1){//check if it is player data (the only input greater than one in size)
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
                else if(timeOrStudentNum == 't'){//check if the given line is the enter time
                    joinTimeQueue->insert(stoi(line)); //adds variable to queue
                    timeOrStudentNum = 's'; // the next time line size == 1, it will be giving the num of students data, so changing the variable for future if statement
                }
                else if(timeOrStudentNum == 's'){//check if given line is num of students entering
                    studentCount += stoi(line); //updates number of students
                    numOfStudentsQueue->insert(stoi(line)); //adds data to queue
                    timeOrStudentNum = 't'; // the next time line size == 1, it will be giving the join time data, so changing the variable for future if statement
                }
            }
        }
    }


    //This initalizes an array in each office that is the size of total number of students. This array is used for moving students from one office to another
    registrar->makeQueuePrepArray(studentCount);
    finAid->makeQueuePrepArray(studentCount);
    cashier->makeQueuePrepArray(studentCount);

    stuArray = new Customer*[studentCount]; //adding student queue to student array
    int index = -1;

    while(!(studentQueue->isEmpty())){ //adding queue to array (we can no longer use queue, because we will need to access multiple indexes, but could not use an array before, because we did not know the size)
        stuArray[++index] = studentQueue->remove();
    }

    delete studentQueue;
    
    time = 1;

    //Below used for adding new students to their first queues. Explination seen in for loop comment
    int stuJoinIndex = 0;
    int studentmax;
    int newStudentMax = 0;
    int currentStudentNum = 0;


    while(studentsNotDone()){ //will keep looping until all students are done
        if(!(joinTimeQueue->isEmpty()) && time == joinTimeQueue->peek()){//time is equal to next student join time
            joinTimeQueue->remove(); //we no longer need this, so we remove it from the queue
            stuJoinIndex = newStudentMax;
            studentmax = numOfStudentsQueue->remove();

            for(int i = stuJoinIndex; i < (stuJoinIndex + studentmax); ++i){ //loops through student array, starting at the index 1 more than the last index, and continuing for the number of students to be added (so if it is time 2, and at time 2, 3 students enter, and 4 students have already entered, i, will start at 3, and iterate to 6)
                ++currentStudentNum;
                if(stuArray[i]->getNextOffice() == 'F'){ //checks where student starts, then adds them to that office
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
            if(stuArray[i]->needsNewQueue()){ //if after time increment, student needs a new queue, adds student to that queue
                if(stuArray[i]->getNextOffice() == 'F'){
                    finAid->prepStudentForQueue(stuArray[i]); //special method for when student is moving from one office to another
                }
                else if(stuArray[i]->getNextOffice() == 'R'){
                    registrar->prepStudentForQueue(stuArray[i]);
                }
                else if(stuArray[i]->getNextOffice() == 'C'){
                    cashier->prepStudentForQueue(stuArray[i]);
                }
            }
        }

        // goes back and adds students from other offices to the queue they want to move to
        finAid->addQueueFromOtherOffice();
        registrar->addQueueFromOtherOffice();
        cashier->addQueueFromOtherOffice();
    }
    //print stuff
    printFinalData();

    }
    else{
        cerr << "Please put in a correctly formatted file name. File may be broken" << endl;
    }
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

ServiceCenter::ServiceCenter(){}