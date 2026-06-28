#pragma once
/*
 * x: 5 bit
 * y: 5 bit
 * z: 5 bit
 * startch_x: 5 bit
 * startch_y: 5 bit
 * id: 7 bit
 *
 * 32 bits total
 */
typedef struct {
	unsigned int x:  5;
	unsigned int y:  5;
	unsigned int z:  5;
	unsigned int sx: 5;
	unsigned int sy: 5;
	unsigned int id: 7;
} square_t;

typedef struct {
	std::vector<square_t> squares;

	unsigned int facing: 4;
} chunk_part_t;

typedef struct {
	/*
	 * X+ 0  xyz
	 * X- 1  
	 * Y+ 2  yzx
	 * Y- 3  
	 * Z+ 4  zyx
	 * Z- 5  
	 * chunk_parts scheme
	 */
	chunk_part_t chunk_parts[6]; 
	int x; int y ;int z;
} chunk_t;

//CHANGES
typedef struct {
	unsigned int x:  5;
	unsigned int y:  5;
	unsigned int z:  5;

	uint8_t id;
} voxel_t;

typedef struct {
	int x; int y; int z;
	std::vector<voxel_t> changed_voxels;
} chunk_changes_t;

class World {
public:
	int seed;

	unsigned int VAO, VBO;

	unsigned int half_x_dist;
	unsigned int half_y_dist;
	unsigned int half_z_dist;
	int center_x; int center_y; int center_z;

	std::vector<chunk_t> loaded_chunks; // with sizeof  hxd * hyd * hzd
	std::vector<chunk_changes_t> changes;

	World(glm::vec3 dist_sizes, int nseed);
	
	void generate_world_mesh(glm::vec3 new_center);
	void prepare_buffers();
	void draw();
};
