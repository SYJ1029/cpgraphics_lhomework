#version 330 core

layout (location = 0) in vec3 vPos;       //--- 버텍스 위치
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 inColor;

out vec3 FragPos;                        //--- 객체의 위치값을 프래그먼트 셰이더로 보냄
out vec3 FragNormal;
out vec3 outColor;

uniform mat4 modelTransform;                      //--- 모델링 변환값
uniform mat4 viewTransform;                       //--- 뷰잉 변환값
uniform mat4 projectionTransform;                 //--- 투영 변환값

void main() {
    gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vPos, 1.0);
    FragPos = vec3(modelTransform * vec4(vPos, 1.0)); 
    FragNormal = aNormal;
    outColor = inColor;
}