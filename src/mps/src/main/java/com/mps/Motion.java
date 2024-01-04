package com.mps;

public class Motion {

    public final int X = 0; //xyz index values signifiying [x,y,z] format in a vector
    public final int Y = 1;
    public final int Z = 2;

    private Particle p;
    private float[] velocity;
    private float[] acceleration;

    public Motion(Particle p, float[] velocity){

        this.p = p;
        this.velocity = velocity;

    }

    public Particle setVelocity(Particle part, float[] velocity){

        this.velocity = velocity;
        
        float[] newPos = part.getPosition();

        newPos[X] += velocity[X]; newPos[Y] += velocity[Y]; newPos[Z] += velocity[Z]; //Adding xyz values of m to position
        
        part.setPosition(newPos);

        return part;

    }


    public float[] getVelocity(){return this.velocity;}
    public float[] getAcceleration(){return this.acceleration;}

    


    
}
