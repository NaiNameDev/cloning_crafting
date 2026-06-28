#include <voxel_backrooms/world.hpp>

World::World(glm::vec3 dist_sizes, int nseed) {
	half_x_dist = (unsigned int)floor(dist_sizes.x);
	half_y_dist = (unsigned int)floor(dist_sizes.y);
	half_z_dist = (unsigned int)floor(dist_sizes.z);

	center_x = 0;
	center_y = 0;
	center_z = 0;

	seed = nseed;

	loaded_chunks.resize((half_x_dist*2+1) * (half_y_dist*2+1) * (half_z_dist*2+1));
}

// now its generate only 1 center chunk
void World::generate_world_mesh(glm::vec3 new_center) {
	chunk_t nch;
	nch.x = 0;
	nch.y = 0;
	nch.z = 0;
	//FREE THIS SHIT
	nch.chunk_parts[0].facing = 0;

	std::mt19937 gen(seed);
	std::uniform_int_distribution<int> dist(0, 7); 
	
	for (unsigned char i = 0; i < 32; i++) {
		for (unsigned char j = 0; j < 32; j++) {
			for (unsigned char k = 0; k < 32; k++) {
				int rnd = (int)dist(gen);

				//if (rnd == 1) {
					square_t nsq = (square_t){i,j,k,0,0,0xf};

					nch.chunk_parts[0].squares.push_back(nsq);
					std::cout << nsq.x << " " << nsq.y << " " << nsq.z << "\n";
				//}
			}
		}
	}
	loaded_chunks[0] = nch;
}

void World::prepare_buffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, (long int)loaded_chunks[0].chunk_parts[0].squares.size(), (const void*)loaded_chunks[0].chunk_parts[0].squares.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 1, GL_INT, GL_FALSE, sizeof(int), (void*)0);
	glEnableVertexAttribArray(0);
}

void World::draw() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, (long int)loaded_chunks[0].chunk_parts[0].squares.size());
}
