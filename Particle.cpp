

#include "Particle.h"

Particle::Particle()
{
    
}

Particle::Particle( const Vector3d &p, const Vector3d &v, const Vector3d &a, const float l, const int age)
{
    setParticlev(v);
    setParticlep(p);
    setParticlea(a);
    setParticlel(l);
    setParticleage(age);
}

Particle::~Particle()
{
    
}

void Particle::setParticlev(const Vector3d &v)
{
    Particle::Velocity = v;
}

void Particle::setParticlep(const Vector3d &p)
{
    Particle::Position = p;
}

void Particle::setParticlea(const Vector3d &a)
{
    Particle::Acceleration = a;
}

void Particle::setParticlel(const float l)
{
    Particle::lifespan = l;
}

void Particle::setParticleage(const int age)
{
    Age  = age;
}

void Particle::simulate(const double timestep)
{
    update(timestep);
    DrawParticle(Position.x, Position.y, Position.z);
}

void Particle::update(const double timestep)
{
    std::cout<<"p y"<<Position.y<<std::endl;
    std::cout<<"vel y"<<Velocity.y<<std::endl;
    Vector3d singularity(0.0,0.0,0.0);
    Vector3d centerSphere(0.5,1.0,0.5);
    std::cout<<"Norms"<<(Position - centerSphere).norm()<<std::endl;
    
  
    
    
    Vector3d UnitSingularity = (singularity - Position).normalize()*0.1;
    
    Velocity = UnitSingularity;
    
    
    //double ts= 0.07;
    Position.x = Position.x + (Velocity.x * timestep);
    Position.y = Position.y + (Velocity.y * timestep);
    Position.z = Position.z + (Velocity.z * timestep);
    //update velocity,position, acceleration, lifespan and time of a particle
    //std::cout<<Velocity.y<<std::endl;
    std::cout<<Position.y<<std::endl;
    
    if ((Position - centerSphere).norm()< 0.05)
    {
        std::cout<<"collision has occured"<<std::endl;
        Velocity = 0;
    }
}


void Particle::DrawParticle (float x, float y, float z)
{
    
    glBegin(GL_POINTS);
    glVertex3f(x,y,z);
    glEnd();
    
    
    /*
    
    glPushMatrix();
    glTranslatef (x,y,z);
    glutSolidSphere(0.01,40,40);
    glPopMatrix ();
     */
    
    glFlush();
}

int Particle::isAlive()
{
    if (Age < lifespan)
    {
        return 1;
    }
    else
    {
        return 0;
    }
   
}



