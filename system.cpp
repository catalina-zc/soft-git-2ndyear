#include <iostream>
#include "system.h"

System::System(int particleNumber,double sideLength, double timeStep,double noiseStrength,int seed){
    
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

void System::randomStart(){
    for (Particle &p : this-> particles){
        p.x = this->uniform(0,this->simulationBox.getSidex());
        p.y = this->uniform(0,this->simulationBox.getSidex());
        p.theta = this->uniform(-M_PI,M_PI);
    }
}

void System::updateRule() {
    std::vector<double> new_theta(particleNumber);
    double Lx = this->simulationBox.getSidex();
    double Ly = this->simulationBox.getSidey();

    for (int i = 0; i < particleNumber; i++){

        int count = 1;
        double cos = std::cos(particles[i].theta);
        double sin = std::sin(particles[i].theta);
        
        for (int j = 0 ; j < particleNumber; j++){

            if (i!=j){
                // calculate distance
                double dx = particles[j].x - particles[i].x;
                double dy = particles[j].y - particles[i].y;

                if(dx>Lx*0.5) dx-=Lx;
                if(dx<-Lx*0.5) dx+=Lx;
                if(dy>Ly*0.5) dy-=Ly;
                if(dy<-Ly*0.5) dy+=Ly;
                
                // calculate the distance between the two particles
                double dist = std::sqrt(dx*dx + dy*dy);
            
                // check if the distance is below the interaction radius
                if (dist < particles[i].r){
                    // calculate the new orientation
                    cos +=  std::cos(particles[j].theta);
                    sin +=  std::sin(particles[j].theta);
                    count+=1;
                }
            }
        }
        
        cos /= count;
        sin /= count;
        // average + noise
        double avg_theta = std::atan2(sin, cos);
        new_theta[i] = avg_theta + this->noiseStrength*this->uniform(-M_PI,M_PI);
    }
    // move the particles
    for (int i = 0; i < particleNumber; i++){
        particles[i].x += std::cos(new_theta[i])*particles[i].v*this->timeStep;
        particles[i].y += std::sin(new_theta[i])*particles[i].v*this->timeStep;
        particles[i].theta = new_theta[i];
        // periodic boundaries
        if (particles[i].x >Lx) particles[i].x -= Lx;
        if (particles[i].x <0) particles[i].x += Lx;
        if (particles[i].y >Ly) particles[i].y -= Ly;
        if (particles[i].y <0) particles[i].y += Ly;
    }
}

double System::uniform(double min,double max) {
    return (max-min)*this->uniformDist(gen)+min;
}

void System::saveConfig(const std::string &filename)
{   
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return; // Exit if file cannot be opened
    }
    outFile << std::to_string(particles.size())+"\nParticles"<<std::endl;
    
    // Write particle properties to the file

    for (size_t i = 0; i < particles.size(); ++i) {
        outFile << i << " " << particles[i].x <<" "<<particles[i].y<<" "<<particles[i].theta << std::endl;
    }
    outFile.close(); // Close the file
}
