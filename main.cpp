#include <iostream>
#include "system.h"
int main(){
    int N = 100;
    double L = 20.0;
    double dt = 0.5;
    double noise = 0.1;
    int seed = 12345;
    System model(N, L, dt, noise,seed);
    std::cout<<"The system contains "<<model.particleNumber<<" particles."<<std::endl;
    std::cout<<"The system has noise "<<model.noiseStrength<<std::endl;
    std::cout<<"The system has a simulation box of side "<<model.simulationBox.getSidex()<<std::endl;
    std::cout<<"A random number between 10 and 20 is: "<<model.uniform(10,20)<<std::endl;
    model.updateRule();
    return 0;
}
