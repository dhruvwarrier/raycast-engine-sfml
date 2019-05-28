
#ifndef MAP_NODE_H
#define MAP_NODE_H

namespace rc {
	// index into the WALL_TEXTURES array where the texture resides
	typedef unsigned int texture_index;

	struct map_node {
		bool wall_present;
		// textures to show on each 
		texture_index left_tex;
		texture_index right_tex;
		texture_index front_tex;
		texture_index back_tex;
	};
}

#endif // MAP_NODE_H