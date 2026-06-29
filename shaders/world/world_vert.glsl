#version 430 core

layout (location = 0) in int data;

flat out uvec2 stretch;
flat out uint id;

void main() {
	uint x = (data >> 0u) & 0x1Fu;
	uint y = (data >> 5u) & 0x1Fu;
	uint z = (data >> 10u) & 0x1Fu;

	stretch.x = (data >> 15u) & 0x1Fu;
	stretch.y = (data >> 20u) & 0x1Fu;
	
	id = (data >> 25u) & 0x7Fu;
	
	gl_Position = vec4(float(x)/31.0, float(y)/31.0, float(z)/31.0, 1.0f);
}
