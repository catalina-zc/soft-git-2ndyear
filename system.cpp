#include <iostream>
#include "system.h"

System::System(int particleNumber,double sideLength, double timeStep,double noiseStrength,int 
seed) {
    
    std::cout<<"I am constructing the System!"<<std::endl;

    this->particleNumber = particleNumber;
    this->noiseStrength = noiseStrength;
    this->timeStep = timeStep;
    this->sideLength = sideLength;

    this->simulationBox = Box(sideLength,sideLength,0,0);

    this->particles.resize(this->particleNumber);

    // initialise random number generator
    this->gen = std::mt19937(seed);
}

void System::updateRule() {
    // Implement the logic for updating rules
    std::cout<<"Updating the system..."<<std::endl;
}
double System::uniform(double min,double max) {
    return (max-min)*this->uniformDist(gen)+min;

void System::randomStart(){
    for (Particle &p : this-> particles){
        p.x = this->uniform(0,this->simulationBox.getSidex());
        p.y = this->uniform(0,this->simulationBox.getSidex());
        p.theta = this->uniform(-M_PI,M_PI);
    }

}
