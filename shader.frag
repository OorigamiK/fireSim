#version 330 core
out vec4 FragColor;
in vec3 pos;

uniform samplerBuffer particleData;
uniform float basicData[10];

vec3 rotate(vec3 rayDir, vec2 rot){
    vec3 newDir=rayDir;
    newDir.z=rayDir.y*sin(rot.y)+rayDir.z*cos(rot.y);
    newDir.y=rayDir.y*cos(rot.y)-rayDir.z*sin(rot.y);
    newDir.x=rayDir.x*cos(rot.x)-newDir.z*sin(rot.x);
    newDir.z=rayDir.x*sin(rot.x)+newDir.z*cos(rot.x);
    return newDir;
}

vec2 rayBallIntersection(vec3 rayDir, vec3 rayPos, vec3 spherePos, float r) {
    vec3 oc = rayPos - spherePos;

    float b = dot(rayDir, oc);
    float c = dot(oc, oc) - r * r;
    float discriminant = b * b - c;

    vec2 res = vec2(-1.0); // Default: no intersection
    if (discriminant > 0.0) {
        float sqrtDisc = sqrt(discriminant);
        float t1 = -b - sqrtDisc;
        float t2 = -b + sqrtDisc;
        res = vec2(max(0,t1), max(0,t2));
    }
    return res;
}

float rayTrace(vec3 rayDir, vec3 rayPos, int numOfParticles, int offset){
    float dist=-1;
    for (int i=0;i<numOfParticles;i++){
        float x=texelFetch(particleData, i*offset+0).x;
        float y=texelFetch(particleData, i*offset+1).x;
        float z=texelFetch(particleData, i*offset+2).x;

        vec3 spherePos=vec3(x,y,z);
        float disToParticle0=rayBallIntersection(rayDir, rayPos, spherePos,1).x;
        if (dist==-1 || (disToParticle0<dist && disToParticle0>0)){
            dist = disToParticle0;
        }
    }
    return dist;
}

void main()
{
    FragColor = vec4(0, 0, 0, 1);
    int numOfParticles=int(basicData[0]+0.5);
    int offset=int(basicData[1]+0.5);
    vec3 rayPos=vec3(basicData[2], basicData[3], basicData[4]);
    vec3 rayDir=normalize(vec3(pos.x, pos.y, 1));
    rayDir=rotate(rayDir, vec2(basicData[5], basicData[6]));

    float disToParticle=rayTrace(rayDir, rayPos, numOfParticles, offset);

    if (disToParticle>0){
        FragColor=vec4(1,0,0,1);
    }
}