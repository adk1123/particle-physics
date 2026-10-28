#ifndef SMALLPARTICLE_H
#define SMALLPARTICLE_H


#include "vec3.h"



typedef struct smallparticle
{
    Vec3 pos;
    Vec3 vel;
    Vec3 acc;
    
    double mass;
    double charge;
}sp;





#endif