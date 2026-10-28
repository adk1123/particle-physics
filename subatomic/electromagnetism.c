#include <math.h>
#include "vec3.h"  
#include "electromagentism.h"
#include "smallparticle.h"

double seperation(sp *p1, sp *p2){

    double dx = p1->pos.x - p2->pos.x;
    double dy = p1->pos.y - p2->pos.y;
    double dz = p1->pos.z - p2->pos.z;

    double r = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));


    return r;
}