#include <voxel_backrooms/world.hpp>

uint32_t pack_square(square_t sqr) {
	uint32_t ret = 0;
	ret |= (sqr.x & 31) << 0;
	ret |= (sqr.y & 31) << 5;
	ret |= (sqr.z & 31) << 10;
	ret |= (sqr.sx & 31) << 15;
	ret |= (sqr.sy & 31) << 20;
	ret |= (sqr.id & 127) << 25;
	return ret;
}

World::World(glm::vec3 dist_sizes, int nseed) {
	half_x_dist = (unsigned int)floor(dist_sizes.x);
	half_y_dist = (unsigned int)floor(dist_sizes.y);
	half_z_dist = (unsigned int)floor(dist_sizes.z);

	center_x = 0;
	center_y = 0;
	center_z = 0;

	seed = nseed;

	squares_cnt = 0;
	loaded_chunks.resize((half_x_dist*2+1) * (half_y_dist*2+1) * (half_z_dist*2+1));
}

// now its generate only 1 center chunk
void World::generate_world_mesh(glm::vec3 new_center) {
	squares_cnt = 0;
	chunk_t nch;
	nch.x = 0;
	nch.y = 0;
	nch.z = 0;
	nch.chunk_parts[0].facing = 0;

	std::mt19937 gen(seed);
	std::uniform_int_distribution<int> dist(0, 1); 
	
	for (unsigned int i = 0; i < 32; i++) {
		for (unsigned int j = 0; j < 32; j++) {
			for (unsigned int k = 0; k < 32; k++) {
				int rnd = (int)dist(gen);

				//if (rnd == 1) {
					square_t nsq = (square_t){i,j,k,1,1,0};
					nch.chunk_parts[0].raw_squares.push_back(pack_square(nsq));
					squares_cnt++;
				//}
			}
		}
	}
	loaded_chunks[0] = nch;
}

void World::prepare_buffers() {
	/*glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
		GL_ARRAY_BUFFER, 
		squares_cnt * sizeof(int), 
		loaded_chunks[0].chunk_parts[0].raw_squares.data(),
		GL_STATIC_DRAW
	);

	glVertexAttribIPointer(0, 1, GL_INT, sizeof(int), (void*)0);
	glEnableVertexAttribArray(0);
	*/

	//DrawElementsIndirectCommand commands[];
}

void World::draw() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, squares_cnt);
}
