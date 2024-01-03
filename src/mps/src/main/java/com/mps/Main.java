package main.java.com.mps;

import java.util.concurrent.TimeUnit;

public class Main {
    
    public static void main(String[] args) {
        
        float[] position = new float[3];

        float[] velocity = new float[]{2.0f,0.0f,0.0f};

        Particle p1 = new Particle(10,position);

        Motion mot = new Motion(p1);

        long start = TimeUnit.MILLISECONDS.toSeconds(System.currentTimeMillis()); //Convert Nanoseconds to Seconds

        long currentTime;

        int counter = 0;

        while(true){
            
            currentTime = TimeUnit.MILLISECONDS.toSeconds(System.currentTimeMillis())-start;

            if(currentTime == counter){

                System.out.println("WORKING");

                mot.setVelocity(p1, velocity);

                counter++;

            }

            
            System.out.println(p1 + ", " + currentTime);
        
    
        }

    }


}
