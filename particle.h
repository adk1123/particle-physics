#ifndef PARTICLE_H
#define PARTICLE_H

#include "vec3.h"
#include "particle.h"

typedef struct Particle{
    
    Vec3 pos;
    Vec3 vel;
    Vec3 acc;

    double mass;

}p;

#endif