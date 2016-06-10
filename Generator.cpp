#include "Generator.h"

#include <vector>

Generator::Generator(const Vector3d &origin, const int noOfParticles, const double timestep)
{
    setGeneratorp(origin);
    setGeneratorSize(noOfParticles);
    setGeneratorts(timestep);
    particles.reserve(noOfParticles);
}

Generator::~Generator()
{
    
}

void Generator::setGeneratorp(const Vector3d &p)
{
    Generator::Origin = p;
   
}

void Generator::setGeneratorSize(const int size)
{
    Generator::noOfParticles = size;
    
}

void Generator::setGeneratorts(const double timestep)
{
    timeStep = timestep;
    
}

double Generator::RandomDouble(double a, double b) {
    double random = ((double) rand()) / (double) RAND_MAX;
    double diff = b - a;
    double r = random * diff;
    return a + r;
}

void Generator::addParticles()
{
   
    for (int i= 0; i< noOfParticles; i++)
    {
        addParticle();
        
    }
}


void Generator::addParticle()
{
    double vx = RandomDouble(-0.80,0.90);
    double vy = RandomDouble(0.0,-0.75);
    double vz = RandomDouble(-0.55,0.75);
    
    double x = RandomDouble(0.0,1.0);
    double y = RandomDouble(0.0,1.0);
    double z = RandomDouble(0.0,1.0);
    
    
    Vector3d V2(vx,vy,vz); //random velocity generator
    Vector3d P2(x,y,z);
    Vector3d a(0, 0, 0); //fixed acceleration
    float l = 200; //fixed lifespan and initial position
    int age  = 0;
    particles.push_back(Particle (P2, V2, a, l, age));
}

void Generator::run()
{
    //glutSolidSphere(0.08,40,40);
    for (int i= 0; i< noOfParticles; i++)
    {
        if (particles[i].isAlive())
        {
            particles[i].Age = particles[i].Age + 1;
            particles[i].simulate(timeStep);
            
        }
        else
        {
            particles.erase(particles.begin()+i-1);
            //noOfParticles = noOfParticles -1;
            addParticle();
            
        }
        
        
    
    }


}



