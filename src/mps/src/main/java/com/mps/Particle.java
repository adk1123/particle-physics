package main.java.com.mps;

import java.util.Arrays;

public class Particle {

    private float mass;
    private float[] position;
    
    public Particle(float mass, float[] position){

        this.mass = mass;
        this.position = position;

    }

    public float getMass(){return this.mass;}

    public float[] getPosition(){return this.position;}

    @Override
    public String toString(){return this.mass + ": " + Arrays.toString(position);}
    

}
