package com.mps;

import java.util.concurrent.TimeUnit;

public class Main {
    
    public static void main(String[] args) {
        
        float[] position = new float[3];

        float[] velocity = new float[]{35.0f,35.0f,0.0f};
        
        float[] gravity = new float[]{0.0f,-9.81f,0.0f};

        Particle p1 = new Particle(10,position);

        Motion mot = new Motion(p1,velocity);

        Force force = new Force(p1, mot);

        long start = TimeUnit.MILLISECONDS.toSeconds(System.currentTimeMillis()); //Convert Nanoseconds to Seconds

        long currentTime;

        int counter = 0;

        while(true){
            
            currentTime = TimeUnit.MILLISECONDS.toSeconds(System.currentTimeMillis())-start;

            if(currentTime == counter){

                force.setAcceleration(p1, gravity);

                if(p1.getPosition()[1] <= 0){

                    break;

                }

                counter++;

            }

            
            System.out.println(p1 + ", " + currentTime);
        
    
        }

    }


}
