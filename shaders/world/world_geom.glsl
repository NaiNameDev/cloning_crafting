#version 460 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 fin_mat;
uniform float utime;

in uvec2 stretch[];
in uint id[];

void main() {
	vec4 orig_pos = gl_in[0].gl_Position/32;
	orig_pos.z -= (abs(sin(utime))) + 0.5;
	orig_pos.x += sin(utime) / 11.0;
	orig_pos.y += cos(utime) / 10.0;

	gl_Position = fin_mat * (orig_pos);
    EmitVertex();
	gl_Position = fin_mat * (orig_pos + vec4(0.03125, 0.0, 0.0, 1.0));
    EmitVertex();
	gl_Position = fin_mat * (orig_pos + vec4(0.0, 0.03125, 0.0, 1.0));
    EmitVertex();
	gl_Position = fin_mat * (orig_pos + vec4(0.03125, 0.03125, 0.0, 1.0));
    EmitVertex();
	
	/*gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
    EmitVertex();
	gl_Position = vec4(1.0, 0.0, 0.0, 1.0);
    EmitVertex();
	gl_Position = vec4(1.0, 1.0, 0.0, 1.0);
    EmitVertex();
	gl_Position = vec4(0.0, 1.0, 0.0, 1.0);
    EmitVertex();
	*/
	EndPrimitive();
}
