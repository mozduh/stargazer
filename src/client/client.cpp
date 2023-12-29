#define OLC_PGE_APPLICATION
#include "../shared/olcPixelGameEngine.h"
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

	// Layers to be rendered
	int worldLayer;
	int gameObjLayer;
	int playerObjLayer;
	int interfaceLayer;

	// Map
	SG::world::SGMap *map;

	// Tiles
	

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

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Render Layer 0 - DEBUG
		Clear(olc::BLANK);

		// Render Layer 1 - World
		SetDrawTarget(worldLayer);
		// WORLD DRAWING CRITICAL SECTION

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