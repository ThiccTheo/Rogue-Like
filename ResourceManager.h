#pragma once
#include "Common.h"

class ResourceManager {
public:
	static void loadMedia();
	static Texture tileTexture;
	static Texture playerTexture;
	static Texture skeletonTexture;

	static Image START1;
	static Image LR1;
	static Image LRD1;
	static Image LRU1;
	static Image ALL1;
	static Image EXIT1;

	static const int START_size;
	static const int LR_size;
	static const int LRD_size;
	static const int LRU_size;
	static const int ALL_size;
	static const int EXIT_size;

	static Image START_array[];
	static Image LR_array[];
	static Image LRD_array[];
	static Image LRU_array[];
	static Image ALL_array[];
	static Image EXIT_array[];

};