#include "ServiceCenter.h"

int main(int argc, char** argv){
    cout << "YEP" << endl;
    ServiceCenter* sc = new ServiceCenter("input.txt");
    delete sc;
}