#include "../../../shared/olcPixelGameEngine.h"
#include "map.h"


SG::world::SGMap::SGMap(olc::vi2d mapSize) 
{
    vMapSize = mapSize;

    // Load sprites used in demonstration
    sprIsom = new olc::Sprite("../assets/isometric_demo.png");

    // Create empty world
    pWorld = new int[vMapSize.x * vMapSize.y]{ 0 };
}