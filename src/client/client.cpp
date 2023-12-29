#define OLC_PGE_APPLICATION
#include "../../shared/olcPixelGameEngine.h"
#include "./include/map.h"
#include "./include/tile.h"

// Override base class with your custom functionality
class StarGazerGame : public olc::PixelGameEngine
{
public:
	StarGazerGame()
	{
		sAppName = "Star Gazer";
	}

private:
	// Number of tiles in world
	olc::vi2d vWorldSize = { 14, 10 };

	// Size of single tile graphic
	olc::vi2d vTileSize = { 40, 20 };

	// Where to place tile (0,0) on screen (in tile size steps)
	olc::vi2d vOrigin = { 5, 1 };

	// Sprite that holds all imagery
	olc::Sprite *sprIsom = nullptr;

	// Pointer to create 2D world array
	int *pWorld = nullptr;

	// SG::world::SGMap map = SG::world::SGMap(vWorldSize);
	SG::world::SGTile selectedTile = SG::world::SGTile(vTileSize, 0, 0, 1, 1);
	SG::world::SGTile invisbleTile = SG::world::SGTile(vTileSize, 1, 0, 1, 1);
	SG::world::SGTile grassTile = SG::world::SGTile(vTileSize, 2, 0, 1, 1);
	SG::world::SGTile sandTile = SG::world::SGTile(vTileSize, 2, 1, 1, 2);
	SG::world::SGTile widtheredTreeTile = SG::world::SGTile(vTileSize, 1, 1, 1, 2);
	SG::world::SGTile treeTile = SG::world::SGTile(vTileSize, 0, 1, 1, 2);
	SG::world::SGTile waterTile = SG::world::SGTile(vTileSize, 3, 1, 1, 2);

public:
	bool OnUserCreate() override
	{
		// Load sprites used in demonstration
		sprIsom = new olc::Sprite("../assets/isometric_demo.png");

		// Create empty world
		pWorld = new int[vWorldSize.x * vWorldSize.y]{ 0 };
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Render Layer 0 - DEBUG
		Clear(olc::WHITE);

		// Render Layer 1 - World

		// Render Layer 2 - GameObjects

		// Render Layer 3 - Interfaces


		return true;
	}
};


int main()
{
	StarGazerGame demo;
	if (demo.Construct(512, 480, 2, 2))
		demo.Start();
	return 0;
}