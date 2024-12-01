#version 330 core

in vec3 FragPos;    //--- 객체의 위치값 (버텍스 셰이더에서 전달받음)
in vec3 Normal;     //--- 노멀 값 (버텍스 셰이더에서 전달받음)
in vec3 outColor; // 파이프라인을 따라 입력 받는 경우 객체의 정점별 색상임

out vec4 FragColor; //--- 최종 픽셀 색상 출력

uniform vec3 lightPos;    //--- 광원의 위치
uniform vec3 viewPos;     //--- 카메라(뷰어)의 위치
uniform vec3 lightColor;  //--- 광원의 색상
uniform vec3 objectColor; //--- 객체의 색상
uniform int onLight;

void main() {
    vec3 result;

    // Ambient (주변 조명)
    float ambientStrength = 0.3; //--- 주변 조명 계수
    vec3 ambient = ambientStrength * lightColor; //--- 주변 조명 값

    // Diffuse (산란 반사 조명)
    vec3 norm = normalize(Normal);                  //--- 노멀 벡터 정규화
    vec3 lightDir = normalize(lightPos - FragPos);  //--- 광원 방향 벡터
    float diff = max(dot(norm, lightDir), 0.0);     //--- 내적 값 계산 (음수 방지)
    vec3 diffuse = diff * lightColor;               //--- 산란 반사 조명 값

    // Specular (거울 반사 조명)
    int shininess = 128;                            //--- 광택 계수
    vec3 viewDir = normalize(viewPos - FragPos);    //--- 관찰자 방향 벡터
    vec3 reflectDir = reflect(-lightDir, norm);     //--- 반사 방향 벡터
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); //--- 거울 반사 강도 계산
    vec3 specular = spec * lightColor;              //--- 거울 반사 조명 값

    // Combine results (최종 조명 값 계산)
    if(onLight == 1)
        result = (ambient + diffuse + specular) * outColor; //--- 조명 값 * 객체 색상
    else
        result = outColor; //--- 객체 색상만

    FragColor = vec4(result, 1.0);                 //--- 최종 픽셀 색상 출력
}
