#version 330 core

layout (location = 0) in vec3 vPos;       //--- ���ؽ� ��ġ
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 inColor;

out vec3 FragPos;                        //--- ��ü�� ��ġ���� �����׸�Ʈ ���̴��� ����
out vec3 FragNormal;
out vec3 outColor;

uniform mat4 modelTransform;                      //--- �𵨸� ��ȯ��
uniform mat4 viewTransform;                       //--- ���� ��ȯ��
uniform mat4 projectionTransform;                 //--- ���� ��ȯ��

void main() {
    gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vPos, 1.0);
    FragPos = vec3(modelTransform * vec4(vPos, 1.0)); 
    FragNormal = aNormal;
    outColor = inColor;
}