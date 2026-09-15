#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "vec3.h"
#include "particle.h"
#include "map.h"

#define GRAVITY -9.81;
#define MS 0.001;

extern void setVec3(Vec3 *v, double x, double y, double z);
extern Vec3 vecAdd(Vec3 *v1, Vec3 *v2);
extern Vec3 calcForce(Vec3 acc, double mass);
extern Vec3 calcDrag(Vec3 *vel, double fluid_density, double *drag_co, double area);
extern void applyForce(p *p, Vec3 *force);
extern Vec3 vecScaleMult(Vec3 v, double scale);

extern void updatePosition(p *p, double dt);;
extern void updateVelocity(p *p, double dt, Vec3 initAcc);

extern double calcKineticEnergy(p *p);

extern double calcAtmosphereDensity(p *p);
extern double calcDragCo(p *p, double *drag_co);

extern HashMap* buildG1Map();
extern double getG1DragCo(p *p, HashMap *g1);

void printParticle(p *p){
    
    printf("position: [%f, %f, %f]\n", p->pos.x, p->pos.y, p->pos.z);
    printf("velocity: [%f, %f, %f]\n", p->vel.x, p->vel.y, p->vel.z);
    printf("acceleration: [%f, %f, %f]\n\n", p->acc.x, p->acc.y, p->acc.z);

}

void runSimulation(p *p, double update, double drag_co, double area, Vec3 *thrust, int duration){

    double t = 0;
    double maxY = 0;
    double maxYAcc = 0;
    double maxXAcc = 0;

    Vec3 vecthrust;
    setVec3(&vecthrust, 0.0, 0.0, 0.0);

    Vec3 gravity;
    setVec3(&gravity, 0.0, -9.81, 0.0);
    
    while(p->pos.y >= 0.0){

        if(t < duration && t > 1000){ 

            setVec3(&vecthrust, thrust->x, thrust->y, thrust->z);
        
        }else{
            
            setVec3(&vecthrust, 0.0, 0.0, 0.0);
        }

        if(p->vel.y <= 0.0 && maxY < p->pos.y){

            maxY = p->pos.y;
        }

        if(maxYAcc >= p->acc.y){

            maxYAcc = p->acc.y;
        }

        if(maxXAcc >= p->acc.x){

            maxXAcc = p->acc.x;
        }
        updatePosition(p, update);
        
        Vec3 initAcc = p->acc;
        double drag_co_calc = calcDragCo(p, &drag_co);
        double density = calcAtmosphereDensity(p);
        Vec3 gravityForce = calcForce(gravity, p->mass);
        Vec3 dragForce = calcDrag(&p->vel, density, &drag_co_calc, area);
        
        Vec3 total_Force = vecAdd(&gravityForce, &dragForce);
        total_Force =  vecAdd(&total_Force, &vecthrust);
        applyForce(p, &total_Force);

        updateVelocity(p, update, initAcc);

        t++;
    }

    double k_energy = calcKineticEnergy(p);

    printParticle(p);
    printf("final time: %f ms\n", t);
    printf("maximum height: %f m\n", maxY);
    printf("maximum acceleration y: %f m/s^2\n", maxYAcc);
    printf("maximum acceleration x: %f m/s^2\n", maxXAcc);
    printf("final kinetic energy: %f J\n", k_energy);
}



int main(){

    p* m114 = malloc(sizeof(p));
    p* federal9mm = malloc(sizeof(p));
    p* nato762 = malloc(sizeof(p));
    p* l16mortar = malloc(sizeof(p));
    p* gustav = malloc(sizeof(p));

    //SET ALL FIELDS OR ELSE ATTRIBUTES OF THE OBJECT WILL POINT TO GARBAGE!!!
    setVec3(&m114->pos, 0.0, 1.5, 0.0);
    setVec3(&m114->vel, 398.81, 398.81, 0.0);
    setVec3(&m114->acc, 0.0, 0.0, 0.0);

    setVec3(&federal9mm->pos, 0.0, 1.5, 0.0);
    setVec3(&federal9mm->vel, 0.0, 290.2, 0.0);
    setVec3(&federal9mm->acc, 0.0, 0.0, 0.0);

    setVec3(&nato762->pos, 0.0, 1.5, 0.0);
    setVec3(&nato762->vel, 849.75, 74.34, 0.0);
    setVec3(&nato762->acc, 0.0, 0.0, 0.0);

    setVec3(&l16mortar->pos, 0.0, 1.0, 0.0);
    setVec3(&l16mortar->vel, 159.95, 159.43, 0.0);
    setVec3(&l16mortar->acc, 0.0, 0.0, 0.0);

    setVec3(&gustav->pos, 0.0, 1.0, 0.0);
    setVec3(&gustav->vel, 579.83, 579.83, 0.0);
    setVec3(&gustav->acc, 0.0, 0.0, 0.0);

    federal9mm->mass = 0.0062;
    m114->mass = 43.0;
    nato762->mass = 0.0255;
    l16mortar->mass = 4.2;
    gustav->mass = 4800.0;

    Vec3* thrust = malloc(sizeof(Vec3)); 
    setVec3(thrust, 250000.0, 250000.0, 0.0);

    printf("\nSchwerer Gustav\n");
    runSimulation(gustav, 0.001, 0.18, 0.5153, thrust, 5000);
    // printf("\nL16 Mortar\n");
    // runSimulation(l16mortar, 0.001, 0.18, 0.00515);
    // printf("\nM114\n");
    // runSimulation(m114, 0.001, 0.18, 0.01887);
    // printf("\n.380 ACP\n");
    // runSimulation(federal9mm, 0.001, 0.38, .0000636);

    free(m114);
    free(federal9mm);
    free(nato762);
    free(l16mortar);
    free(gustav);
}