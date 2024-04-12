//TODO: Registrar subclass of office class


ServiceCenter::ServiceCenter(string fileName){
    //read file stuff



    string line; //string for reading input file
    int count = -1; //int for indexing through gameData
    ifstream readFile(fileName);
    
    int playerCount = 0;
    int* playerAddInfo = new int[];
    if(readFile.is_open()){//reading file and adding it to array
        while(getline(readFile,line)){
            ++count;
            if(count == 0){
                registrarSim = new registrar(stoi(line)); //TODO: need to import something???
            }
            else if(count = 1){
                cashierSim = new cashier(stoi(line));
            }
            else if(count = 2){
                finAidSim = new finAid(stoi(line));
            }
            else{
                
            }
        }
    }




    while(){//Students aren't done
        if(){//time is equal to next student join time
            //add student to queue
        }
        //decrease current student wait times for those at front
        if(){//student finished
        //move them around
        }
        ++time;
    }

    //print stuff
}