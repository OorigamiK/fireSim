#version 330 core
out vec4 FragColor;
in vec3 pos;

uniform samplerBuffer particleData;
uniform float basicData[10];

vec3 rotate(vec3 rayDir, vec2 rot){
    vec3 newDir=rayDir;
    newDir.y=rayDir.y*sin(rot.y)+rayDir.z*cos(rot.y);
    newDir.z=rayDir.y*cos(rot.y)-rayDir.z*sin(rot.y);
    newDir.x=rayDir.x*cos(rot.x)-newDir.z*sin(rot.x);
    newDir.z=rayDir.x*sin(rot.x)+newDir.z*cos(rot.x);
    return newDir;
}

void main()
{
    FragColor = vec4(0, 0, 0, 1);
    int numOfParticles=int(basicData[0]+0.5);
    int offset=int(basicData[1]+0.5);
    vec3 rayPos=vec3(-25, 0, 0);
    vec3 rayDir=normalize(vec3(pos.x, pos.y, 1));
    rayDir=rotate(rayDir, vec2(basicData[5], basicData[6]));


}