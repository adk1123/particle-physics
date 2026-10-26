#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "vec3.h"
#include "particle.h"

#define LIGHT_SPEED 299792458.0;

void setVec3(Vec3 *v, double x, double y, double z){

    v->x = x;
    v->y = y;
    v->z = z;
}

Vec3 vecAdd(Vec3 *v1, Vec3 *v2){

    Vec3 v3;

    v3.x = v1->x + v2->x;
    v3.y = v1->y + v2->y;
    v3.z = v1->z + v2->z;

    return v3;

}

Vec3 vecMult(Vec3 v1, Vec3 v2){

    Vec3 v3;

    v3.x = v1.x * v2.x;
    v3.y = v1.y * v2.y;
    v3.z = v1.z * v2.z;

    return v3;
}

Vec3 vecScaleAdd(Vec3 v, double scale){

    Vec3 vResult;

    vResult.x = v.x + scale;
    vResult.y = v.y + scale;
    vResult.z = v.z + scale;
    
    return vResult;
}

Vec3 vecScaleMult(Vec3 v, double scale){

    Vec3 vResult;

    vResult.x = v.x * scale;
    vResult.y = v.y * scale;
    vResult.z = v.z * scale;
    
    return vResult;
}

double vecMagnitude(Vec3 *v){

    double mag = pow(v->x,2) + pow(v->y,2) + pow(v->z,2);
    return sqrt(mag);
}