#version 460 core

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(std430, binding = 0) buffer data {
    int val;
};

void main() {
	val = 235789239;
}
