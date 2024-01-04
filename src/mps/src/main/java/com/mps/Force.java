package com.mps;

public class Force {

    public final int X = 0; //xyz index values signifiying [x,y,z] format in a vector
    public final int Y = 1;
    public final int Z = 2;
    
    private Particle p;
    private float[] acceleration;
    private Motion motion;

    public Force(Particle p, Motion motion){

        this.p = p;
        this.motion = motion;

    }

    public Particle setAcceleration(Particle part, float[] acceleration){

        this.acceleration = acceleration;

        float[] newVelo = motion.getVelocity();
        
        newVelo[X] += acceleration[X]; newVelo[Y] += acceleration[Y]; newVelo[Z] += acceleration[Z]; //Addig xyz values of m/s to velocity

        motion.setVelocity(part, newVelo);
        
        return part;


    }



}
