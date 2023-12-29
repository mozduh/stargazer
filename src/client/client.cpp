#define OLC_PGE_APPLICATION
#include "../shared/olcPixelGameEngine.h"
#include "./include/map.h"
#include "./include/tile.h"
#include <typeinfo>
#include <list>

// Override base class with your custom functionality
class StarGazerGame : public olc::PixelGameEngine
{
public:
	StarGazerGame()
	{
		sAppName = "Star Gazer";
	}

private:

	// Layers to be rendered
	int worldLayer;
	int gameObjLayer;
	int playerObjLayer;
	int interfaceLayer;

	// Map
	SG::world::SGMap *map;

	// Tiles TODO
	SG::world::SGTile **tiles;

	// utils DELETE LATER
	SG::world::SGTile tile = SG::world::SGTile("grass");

	// Size of single tile graphic
	olc::vi2d vTileSize = { 40, 20 };

	// Where to place tile (0,0) on screen (in tile size steps)
	olc::vi2d vOrigin = { 5, 1 };


public:
	bool OnUserCreate() override
	{
		// Create Layers
		worldLayer = CreateLayer();
		gameObjLayer = CreateLayer();
		playerObjLayer = CreateLayer();
		interfaceLayer = CreateLayer();

		// initalize map
		// TODO -> this information should come from the server
		std::string mapName = "origin";
		map = new SG::world::SGMap(mapName);

		// initalize tiles used in map
		tiles = new SG::world::SGTile*[map->tileCount];
		for (int i = 0; i < map->tileCount; i++)
		{
			tiles[i] = new SG::world::SGTile(map->tiles[i]);
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		// Labmda function to convert "world" coordinate into screen space
		auto ToScreen = [&](int x, int y)
		{			
			return olc::vi2d
			{
				(vOrigin.x * vTileSize.x) + (x - y) * (vTileSize.x / 2),
				(vOrigin.y * vTileSize.y) + (x + y) * (vTileSize.y / 2)
			};
		};

		// Render Layer 0 - DEBUG
		Clear(olc::BLANK);

		SetPixelMode(olc::Pixel::MASK);


		// Render Layer 1 - World
		SetDrawTarget(worldLayer);
		// WORLD DRAWING CRITICAL SECTION
		for (int y = 0; y < map->mapSize_y; y++)
		{
			for (int x = 0; x < map->mapSize_x; x++)
			{
				olc::vi2d vWorld = ToScreen(x, y);
				SG::world::SGTile tile = *tiles[map->pWorld[(y * (map->mapSize_x)) + x]];
				if (tile.h == tile.tileSize_y * 2) 
				{
					DrawPartialSprite(vWorld.x, vWorld.y - vTileSize.y, map->spriteSheet, tile.ox, tile.oy, tile.w, tile.h);
				}
				else 
				{
					DrawPartialSprite(vWorld.x, vWorld.y, map->spriteSheet, tile.ox, tile.oy, tile.w, tile.h);
				}
				//DrawPartialDecal(vWorld, map->decal, {tile.ox, tile.oy}, {tile.w, tile.h});
			}
		}

		EnableLayer(worldLayer, true);

		// Render Layer 2 - GameObjects
		SetDrawTarget(gameObjLayer);
		// GAME OBJECT DRAWING CRITICAL SECTION

		EnableLayer(gameObjLayer, true);

		// Render Layer 3 - Players
		SetDrawTarget(playerObjLayer);
		// PLAYER DRAWING CRITICAL SECTION

		EnableLayer(playerObjLayer, true);

		// Render Layer 3 - Interfaces
		SetDrawTarget(interfaceLayer);
		// INTERFACE DRAWING CRITICAL SECTION

		EnableLayer(interfaceLayer, true);

		SetPixelMode(olc::Pixel::NORMAL);
		SetDrawTarget(nullptr);
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