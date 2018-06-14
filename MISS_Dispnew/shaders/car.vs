#version 330 core

layout (location = 0) in vec4 v_basePosition;
layout (location = 1) in vec4 v_normal;
layout (location = 2) in vec4 oColor;

layout (location = 3) in vec4 v_instanceOffset;
layout (location = 4) in vec4 m_instanceRotation;

uniform mat3 mat_n;
uniform mat4 mat_mv;
uniform mat4 mat_mvp;
uniform vec3 vLightPosition;

uniform float t;

smooth out vec4 vVColor;

void main(void)
{	
	mat4 rotmat = mat4(
		vec4(m_instanceRotation.x, 0.0, m_instanceRotation.z, 0.0),
		vec4(0.0, 1.0, 0.0, 0.0),
		vec4(m_instanceRotation.y, 0.0, m_instanceRotation.w, 0.0),
		vec4(0.0, 0.0, 0.0, 1.0));
	

	vec4 vPosition = rotmat * v_basePosition;
	vPosition += v_instanceOffset;
	
	vec4 diffuseColor = oColor;
	
	// Obliczanie normalnej do powierzchni we współrzędnych oka
	vec3 vEyeNormal = mat_n * v_normal.xyz;

	// Obliczenie położenia wierzchołka we współrzędnych oka
	vec4 vPosition4 = mat_mv * vPosition;
	vec3 vPosition3 = vPosition4.xyz / vPosition4.w;

	// Obliczenie wektora do źródła światła
	vec3 vLightDir = vLightPosition - vPosition3;

	// Obliczenie intensywności światła przy użyciu iloczynu skalarnego
	float diff = dot(normalize(vEyeNormal), normalize(vLightDir)) + 0.5;

	// Mnożenie intensywności przez kolor rozproszenia
	vVColor.rgb = diff * diffuseColor.rgb;
	vVColor.a = diffuseColor.a;
	//vVColor = diffuseColor;
	gl_Position = mat_mvp * vPosition;
}



















