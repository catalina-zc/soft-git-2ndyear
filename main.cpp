#include <iostream>
#include "system.h"
#include <cstdlib>  // For std::stof (string to float)
 
int main(){
    int N = 100;
    double L = 20.0;
    double dt = 0.5;
    double noise = 0.1;
    int seed = 12345;

    System model(N, L, dt, noise,seed);

    //double noiseStrength = std::stof(argv[1]);

    std::cout<<"The system contains "<<model.particleNumber<<" particles."<<std::endl;
    std::cout<<"The system has noise "<<model.noiseStrength<<std::endl;
    std::cout<<"The system has a simulation box of side "<<model.simulationBox.getSidex()<<std::endl;
    std::cout<<"A random number between 10 and 20 is: "<<model.uniform(10,20)<<std::endl;
    model.updateRule();
    
    model.saveConfig("init.conf");
    
    long int iterations = 1000;
    std::string root = "frames/";
    for (int iteration = 0; iteration <iterations;iteration++)
    {   std::cout<<"iteration"<<iteration<<std::endl;
        if (iteration%5==0) model.saveConfig(root+std::to_string(iteration));
        model.updateRule();
    }
    
    return 0;
}
