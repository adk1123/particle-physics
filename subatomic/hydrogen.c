#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "vec3.h"
#include "smallparticle.h"

extern void setVec3(Vec3 *v, double x, double y, double z);
extern double seperation(sp *p1, sp *p2);


int main(){

    sp* proton = malloc(sizeof(sp));
    sp* electron = malloc(sizeof(sp));
    setVec3(&proton->pos, 0,0,0);
    setVec3(&proton->vel, 0,0,0);
    setVec3(&proton->acc, 0,0,0);
    proton->mass = 1.67 * pow(10, -27);
    proton->charge = 1.60 * pow(10, -19);

    setVec3(&electron->pos, (5.29 * pow(10, -11)),0,0);
    setVec3(&electron->vel, 0,0,0);
    setVec3(&electron->acc, 0,0,0);
    electron->mass = 9.11 * pow(10, -32);
    electron->charge = -1.60 * pow(10, -19);

    double r = seperation(proton, electron);

    double t =  5.29 * pow(10, -11);

    printf("Seperation in Meters: %g\n", r);
}



