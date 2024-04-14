#include "ServiceCenter.h"

int main(int argc, char** argv){
    ServiceCenter* sc = new ServiceCenter("input.txt");
    delete sc;
}