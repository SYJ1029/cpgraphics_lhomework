#version 330 core

in vec3 FragPos;    //--- ��ü�� ��ġ�� (���ؽ� ���̴����� ���޹���)
in vec3 Normal;     //--- ��� �� (���ؽ� ���̴����� ���޹���)
in vec3 outColor; // ������������ ���� �Է� �޴� ��� ��ü�� ������ ������

out vec4 FragColor; //--- ���� �ȼ� ���� ���

uniform vec3 lightPos;    //--- ������ ��ġ
uniform vec3 viewPos;     //--- ī�޶�(���)�� ��ġ
uniform vec3 lightColor;  //--- ������ ����
uniform vec3 objectColor; //--- ��ü�� ����
uniform int onLight;

void main() {
    vec3 result;

    // Ambient (�ֺ� ����)
    float ambientStrength = 0.3; //--- �ֺ� ���� ���
    vec3 ambient = ambientStrength * lightColor; //--- �ֺ� ���� ��

    // Diffuse (��� �ݻ� ����)
    vec3 norm = normalize(Normal);                  //--- ��� ���� ����ȭ
    vec3 lightDir = normalize(lightPos - FragPos);  //--- ���� ���� ����
    float diff = max(dot(norm, lightDir), 0.0);     //--- ���� �� ��� (���� ����)
    vec3 diffuse = diff * lightColor;               //--- ��� �ݻ� ���� ��

    // Specular (�ſ� �ݻ� ����)
    int shininess = 128;                            //--- ���� ���
    vec3 viewDir = normalize(viewPos - FragPos);    //--- ������ ���� ����
    vec3 reflectDir = reflect(-lightDir, norm);     //--- �ݻ� ���� ����
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); //--- �ſ� �ݻ� ���� ���
    vec3 specular = spec * lightColor;              //--- �ſ� �ݻ� ���� ��

    // Combine results (���� ���� �� ���)
    if(onLight == 1)
        result = (ambient + diffuse + specular) * outColor; //--- ���� �� * ��ü ����
    else
        result = outColor; //--- ��ü ����

    FragColor = vec4(result, 1.0);                 //--- ���� �ȼ� ���� ���
}
