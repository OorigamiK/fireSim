#include "physics.h"

float maxf(float a, float b){
    if (a<b) {
        return b;
    }
    return a;
}


float W(float r, float h){
    return pow(maxf(0, (1-r/h)), 2);
}

float WNear(float r, float h){
    return pow(maxf(0, (1-r/h)), 3);
}

void calcPressure(float particles[], int numOfParticles, int offset, int index, float h){
    float pressure=0;
    float pressureNear=0;
    float x=particles[index*offset+0];
    float y=particles[index*offset+1];
    float z=particles[index*offset+2];
    for (int i=0;i<numOfParticles;i++){
        if (i==index) continue;
        float x0=particles[i*offset+0];
        float y0=particles[i*offset+1];
        float z0=particles[i*offset+2];
        float temp0=particles[i*offset+3];

        float r=sqrt((x-x0)*(x-x0)+(y-y0)*(y-y0)+(z-z0)*(z-z0));
        if (r<1e-6) continue;
        pressure+=W(r,h)*temp0;
        pressureNear+=WNear(r,h)*temp0;
    }
    particles[index*offset+4]=pressure;
    particles[index*offset+5]=pressureNear;
}

void D(float particles[], int numOfParticles, int offset, int indexI, int indexJ, float h, float deltaTime, float outVec[3]){
    const float kNear=2;
    const float k = 1;
    
    float P=k*particles[offset*indexI+4];
    float PNear=kNear*particles[offset*indexI+5];
    float x=particles[indexI*offset+0];
    float y=particles[indexI*offset+1];
    float z=particles[indexI*offset+2];

    float x0=particles[indexJ*offset+0];
    float y0=particles[indexJ*offset+1];
    float z0=particles[indexJ*offset+2];

    float r=sqrt((x-x0)*(x-x0)+(y-y0)*(y-y0)+(z-z0)*(z-z0));
    if (r < 1e-6 || r>h){
        outVec[0]*=0;
        outVec[1]*=0;
        outVec[2]*=0;
        return;
    }
    float constD=1/r*pow(deltaTime,2)*(P*(1-r/h)+PNear*pow((1-r/h),2));

    outVec[0]=(x-x0)*constD;
    outVec[1]=(y-y0)*constD;
    outVec[2]=(z-z0)*constD;

}

void updateParticle(float particles[], int numOfParticles, int offset, int index, float h, float deltaTime){
    float force[3]={0,0,0};

    for (int j=0;j<numOfParticles;j++){
        if (j==index) continue;
        float force0[3]={0,0,0};
        D(particles, numOfParticles, offset, index, j, h, deltaTime, force0);
        particles[offset*j+0]+=force0[0]/2;
        particles[offset*j+1]+=force0[1]/2;
        particles[offset*j+2]+=force0[2]/2;

        force[0]-=force0[0]/2;
        force[1]-=force0[1]/2;
        force[2]-=force0[2]/2;
    }
    particles[offset*index+0]+=force[0];
    particles[offset*index+1]+=force[1];
    particles[offset*index+2]+=force[2];
}

void update(float particles[], int numOfParticles, int offset, float h, float deltaTime){
    for (int i=0;i<numOfParticles;i++){
        calcPressure(particles, numOfParticles, offset, i, h);
    }

    for (int i=0;i<numOfParticles;i++){
        updateParticle(particles, numOfParticles, offset, i, h, deltaTime);
    }
}