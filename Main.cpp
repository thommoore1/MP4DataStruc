#include "ServiceCenter.h"

int main(int argc, char** argv){
    //if(argc >= 2){
        ServiceCenter* sc = new ServiceCenter("input.txt");
        delete sc;
    //}
    //else{
    //    cerr << "You need to put in your file name" << endl;
    //}
}