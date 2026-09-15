#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vec3.h"
#include "particle.h"
#include "map.h"

#define LIGHT_SPEED 299792458.0;
#define SOUND_SPEED 343.0;

extern void setVec3(Vec3 *v, double x, double y, double z);
extern Vec3 vecAdd(Vec3 v1, Vec3 v2);
extern Vec3 vecScaleMult(Vec3 v, double scale);
extern Vec3 vecMult(Vec3 v1, Vec3 v2);
extern double vecMagnitude(Vec3 *v);
extern void mapInsert(Entry *e, HashMap *map);
extern double mapSearch(HashMap *map, char *key);
Entry* createEntry(char *key, double value);


HashMap* buildG1Map(){

    HashMap* g1 = malloc(sizeof(HashMap));
    g1->capacity = 10;

    Entry *e1 = createEntry("m00", 0.25); 
    Entry *e2 = createEntry("m05", 0.27); 
    Entry *e3 = createEntry("m08", 0.32); 
    Entry *e4 = createEntry("m09", 0.45); 
    Entry *e5 = createEntry("m10", 0.85); 
    Entry *e6 = createEntry("m11", 0.70); 
    Entry *e7 = createEntry("m12", 0.55); 
    Entry *e8 = createEntry("m15", 0.48); 
    Entry *e9 = createEntry("m20", 0.45);
    Entry *e10 = createEntry("m30", 0.42);

    mapInsert(e1, g1);
    mapInsert(e2, g1);
    mapInsert(e3, g1);
    mapInsert(e4, g1);
    mapInsert(e5, g1);
    mapInsert(e6, g1);
    mapInsert(e7, g1);
    mapInsert(e8, g1);
    mapInsert(e9, g1);
    mapInsert(e10, g1);

    return g1;
}

double getG1DragCo(p *p, HashMap *g1){

    double mach = vecMagnitude(&p->vel)/343.0;

    if(mach < 0.5){

        return mapSearch(g1, "m00");
    }else if(mach >= 0.5 && mach < 0.8){

        return mapSearch(g1, "m05");
    }else if(mach >= 0.8 && mach < 1.0){

        return mapSearch(g1, "m08");
    }else if(mach >= 1.0 && mach < 1.1){

        return mapSearch(g1, "m10");
    }else if(mach >= 1.1 && mach < 1.2){

        return mapSearch(g1, "m11");
    }else if(mach >= 1.2 && mach < 1.5){

        return mapSearch(g1, "m12");
    }else if(mach >= 1.5 && mach < 2.0){

        return mapSearch(g1, "m15");
    }else if(mach >= 2.0 && mach < 3.0){

        return mapSearch(g1, "m20");
    }
    else{
        return mapSearch(g1, "m30");
    }
    
}

void updatePosition(p *p, double dt){

    p->pos.x = p->pos.x + (p->vel.x * dt) + ((0.5 * p->acc.x) * (dt * dt));
    p->pos.y = p->pos.y + (p->vel.y * dt) + ((0.5 * p->acc.y) * (dt * dt)); 
    p->pos.z = p->pos.z + (p->vel.z * dt) + ((0.5 * p->acc.z) * (dt * dt));  
}

void updateVelocity(p *p, double dt, Vec3 initAcc){

    while(p->vel.x <= 299792458.0 && p->vel.y <= 299792458.0 && p->vel.z <= 299792458.0 
        && p->vel.x >= -299792458.0 && p->vel.y >= -299792458.0 && p->vel.z >= -299792458.0){

        p->vel.x = p->vel.x + ((0.5 * (initAcc.x + p->acc.x)) * dt);
        p->vel.y = p->vel.y + ((0.5 * (initAcc.y + p->acc.y)) * dt);
        p->vel.z = p->vel.z + ((0.5 * (initAcc.z + p->acc.z)) * dt);

        break;
    }
}


void applyForce(p *p, Vec3 *force){

    p->acc.x = force->x * (1.0/p->mass);
    p->acc.y = force->y * (1.0/p->mass);
    p->acc.z = force->z * (1.0/p->mass);

}
Vec3 calcForce(Vec3 acc, double mass){

    Vec3 force = vecScaleMult(acc, mass);
    return force;

}


// Drag Physics
Vec3 calcDrag(Vec3 *vel, double fluid_density, double *drag_co, double area){

    Vec3 drag;
    Vec3 v_squared;
    double total_drag_co;

    if(vel->x < 0){

        v_squared.x = (vel->x * vel->x);

    }else if(vel->x > 0){v_squared.x = (vel->x * vel->x) * -1.0;}else{v_squared.x = (vel->x * vel->x);}
    
    if(vel->y < 0){

        v_squared.y = (vel->y * vel->y);

    }else if(vel->y > 0){v_squared.y = (vel->y * vel->y) * -1.0;}else{v_squared.y = (vel->y * vel->y);}
    
    if(vel->z < 0){

        v_squared.z = (vel->z * vel->z);

    }else if(vel->z > 0){v_squared.y = (vel->z * vel->z) * -1.0;}else{v_squared.z = (vel->z * vel->z);}

    total_drag_co = 0.5 * fluid_density * *drag_co * area;

    drag = vecScaleMult(v_squared, total_drag_co);

    return drag;
}


//Return speed of sound dependent on atmospheric density fgiven height dependent Temperature
double calcSpeedOfSound(p *p){

    double specific_heat = 1.4; //Dry Air
    double specific_gas = 287.0; // J/kg*K

    double temp = 288.0 - (0.0065 * p->pos.y);
    return sqrt(temp * specific_gas * specific_heat);
}

//Variable drag coefficient dependent on mach using the drag-rise correction factor in a gaussian bump
double calcDragCo(p *p, double *drag_co){

    double drag_rise = 0.09;
    double peak_height = 0.12;
    double peak_center = 1.0;
    double peak_width = 0.10;
    double supersonic_drag = 0.08;
    double supersonic_decay = 0.7;

    double mach = vecMagnitude(&p->vel)/calcSpeedOfSound(p);
    double subsonic = *drag_co + drag_rise * pow(mach, 2);
    double transonic = peak_height / (1 + pow((mach - peak_center)/peak_width, 2));
    double supersonic = supersonic_drag * exp(-supersonic_decay * (mach - 1.0));

    return subsonic + transonic + supersonic;
}

//Earths atmoshphere fluid density model dependent on altitude, pressure, and temperature
double calcAtmosphereDensity(p *p){

    double temp;
    double pressure;
    double density;

    if(p->pos.y < 11000.0){

        temp = 15.04 - (.00649 * p->pos.y);
        pressure = 101.29 * pow(((temp + 273.1)/288.08), 5.256);
        density = pressure/(.2869 * (temp + 273.1));
        return density;
    }else if(p->pos.y >= 11000.0 && p->pos.y < 25000.0){

        temp = -56.46;
        pressure = 22.65 * exp(1.73 - (.000157 * p->pos.y));
        density = pressure/(.2869 * (temp + 273.1));
        return density;
    }else{

        temp = -131.21 + (.00299 * p->pos.y);
        pressure = 2.488 * pow(((temp + 273.1)/216.6), -11.388);
        density = pressure/(.2869 * (temp + 273.1));
        return density;
    }
}

double calcKineticEnergy(p *p){

    double velMag =  vecMagnitude(&p->vel);

    double v_squared = pow(velMag, 2);

    return (p->mass / 2) * v_squared;
}



//An acceleration value that is applied to a particle in the opposite direction of travel
double computeThrust(p *p, Vec3 force){


    return 0;
}

double computeCollision(p *p1, p *p2){

    return 0;
}



