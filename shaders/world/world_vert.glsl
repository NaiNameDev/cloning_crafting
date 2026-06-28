#version 460 core

layout (location = 0) in int data;

out uvec2 stretch;
out uint id;

void main() {
	// 31 is 11111 binary mask
	uint x = data & 0x1f;
	uint y = (data >> 5) & 0x1f;
	uint z = (data >> 10) & 0x1f;

	stretch.x = (data >> 15) & 0x1f;
	stretch.y = (data >> 20) & 0x1f;
	
	id = (data >> 25) & 0x7f;
	
	gl_Position = vec4(float(x), float(y), float(z), 1.0f);
}
