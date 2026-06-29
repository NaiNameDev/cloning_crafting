#version 430 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 fin_mat;
uniform float utime;

flat in uvec2 stretch[];
flat in uint id[];

const float addx = (1.0f/31.0f) * stretch[0].x;
const float addy = (1.0f/31.0f) * stretch[0].y;

void main() {
	vec4 orig_pos = gl_in[0].gl_Position;
	
	orig_pos.z -= 2.0;
	orig_pos.x += sin(utime) / 11.0;
	orig_pos.y += cos(utime) / 10.0;

	gl_Position = fin_mat * (orig_pos);
    EmitVertex();
	gl_Position = fin_mat * (orig_pos + vec4(addx, 0.0, 0.0, 0.0));
    EmitVertex();
	gl_Position = fin_mat * (orig_pos + vec4(0.0, addy, 0.0, 0.0));
    EmitVertex();
	gl_Position = fin_mat * (orig_pos + vec4(addx, addy, 0.0, 0.0));
    EmitVertex();
	
	EndPrimitive();
}
