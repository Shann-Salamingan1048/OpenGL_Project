#version 330 core
out vec4 FragColor;
in vec3 color;
in float scaleColor;

void main()
{
	 vec3 brightened = color * scaleColor;
    
    // Optional: clamp to prevent over-brightness
    brightened = clamp(brightened, 0.0, 1.0);
	FragColor = vec4(brightened,1.0f);
	
}