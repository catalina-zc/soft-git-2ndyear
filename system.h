#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector> //to use standard C++ vectors
#include <random> //to use random number generator
#include "box.h" 
#include "particle.h" 


class System {
    public:
        System(int particleNumber,double sideLength, double timeStep,double noiseStrength,int 
seed);
        int   particleNumber;
        double noiseStrength;
        double sideLength;
        double timeStep;
        
        Box simulationBox;
        std::vector<Particle> particles;
        // random number generator
        std::mt19937 gen;  
        // uniform distribution
        std::uniform_real_distribution<double> uniformDist;
        // function to sample uniformly distributed random numbers
        double uniform(double min, double max);

        void randomStart();
        std::vector<Particle> particles;
        
        void updateRule();

        void saveConfig(const std::string &filename)

        void initialize();

};

#endif
