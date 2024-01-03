package main.java.com.mps;

public class Motion {

    private final int X = 0;
    private final int Y = 1;
    private final int Z = 2;

    private Particle p;

    public Motion(Particle p){

        this.p = p;

    }

    public Particle setVelocity(Particle part, float[] velocity){

        float[] newPos = part.getPosition();

        newPos[X] += velocity[X]; newPos[Y] += velocity[Y]; newPos[Z] += velocity[Z];
        
        part.setPosition(newPos);

        return part;

    }

    


    
}
