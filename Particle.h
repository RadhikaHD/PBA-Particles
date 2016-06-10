
#include "Vector.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>

//#include "GL/gl.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif



class Particle
{
public:
    
     Vector3d Velocity;
     Vector3d Position;
     Vector3d Acceleration;
     float lifespan;
     int Age;
    
    Particle();
    Particle( const Vector3d &p, const Vector3d &v, const Vector3d &a, const float l, const int age);
    ~Particle();

    
    void setParticlev(const Vector3d &v);
    void setParticlep(const Vector3d &p);
    void setParticlea(const Vector3d &a);
    void setParticlel(const float l);
    void setParticleage(const int age);
    
    void simulate(const double timestep);
    void update(const double timestep);
    void DrawParticle (float x, float y, float z);
    
    int isAlive();
    
    
};