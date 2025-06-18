#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform float uTime;  // Raw time from CPU

out float scaleColor;
void main()
{
 // GPU calculates the scale (much faster than CPU)
	float scale = 1.0 + sin(uTime) * 0.5; // Same math, but on GPU
	gl_Position = vec4( -(aPos.x + aPos.x * scale), -(aPos.y + aPos.y * scale), aPos.z + aPos.z* scale, 1.0);
	color = aColor;
	scaleColor = scale;
};