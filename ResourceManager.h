#pragma once
#include "Common.h"

static class ResourceManager {
public:
	static void loadMedia();
	static Texture tileTexture;
	static Texture playerTexture;
	static Texture skeletonTexture;

	static Image DOOR1;
	static Image LR1;
	static Image LRD1;
	static Image LRU1;
	static Image ALL1;

	static Image DOOR_array[];
	static Image LR_array[];
	static Image LRD_array[];
	static Image LRU_array[];
	static Image ALL_array[];

	//DOOR1.loadFromFile("Image/DOOR/DOOR_Test.png");

	///*----------------------------------------*/

	//LR1.loadFromFile("Image/LR/LR1.png");


	///*----------------------------------------*/

	//LRD1.loadFromFile("Image/LRD/LRD_Test.png");


	///*----------------------------------------*/

	//LRU1.loadFromFile("Image/LRU/LRU_Test.png");

	//
	///*----------------------------------------*/

	//ALL1.loadFromFile("Image/ALL/ALL_Test.png");

};