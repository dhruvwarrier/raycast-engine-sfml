
#ifndef MAP_NODE_H
#define MAP_NODE_H

namespace rc
{
	// index into the WALL_TEXTURES array where the texture resides
	typedef unsigned int texture_index;

	struct map_node 
	{
		bool wall_present;
		// textures to show on each 
		texture_index left;
		texture_index right;
		texture_index front;
		texture_index back;
	};
}

#endif