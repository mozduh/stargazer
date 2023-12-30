#include "../shared/common.h"
#include "./include/map.h"
#include "./include/tile.h"
#include "./include/player.h"
#include <unordered_map>
// Override base class with your custom functionality
class StarGazerGame : public olc::PixelGameEngine, olc::net::client_interface<GameMsg>
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

		// Size of single tile graphic
		olc::vi2d vTileSize = { 40, 20 };

		// Where to place tile (0,0) on screen (in tile size steps)
		olc::vi2d vOrigin = { 5, 1 };

		olc::vi2d viewOffset = { 0, 0 };

		// player
		SG::world::Player *player;

	private:
		std::unordered_map<uint32_t, sPlayerDescription> mapObjects;
		uint32_t nPlayerID = 0;
		sPlayerDescription descPlayer;

		bool bWaitingForConnection = true;

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
			player = new SG::world::Player();

			// initalize tiles used in map
			tiles = new SG::world::SGTile*[map->tileCount];
			for (int i = 0; i < map->tileCount; i++)
			{
				tiles[i] = new SG::world::SGTile(map->tiles[i]);
			}

			// Network Connect
			if (Connect("127.0.0.1", 60000))
			{
				
				return true;
			}

			return false;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{
			// Check for incoming network messages
			if (IsConnected())
			{
				while (!Incoming().empty())
				{
					auto msg = Incoming().pop_front().msg;

					switch (msg.header.id)
					{
					case(GameMsg::Client_Accepted):
					{
						std::cout << "Server accepted client - you're in!\n";
						olc::net::message<GameMsg> msg;
						msg.header.id = GameMsg::Client_RegisterWithServer;
						descPlayer.vPos = { 3, 3 };
						msg << descPlayer;
						Send(msg);
						break;
					}

					case(GameMsg::Client_AssignID):
					{
						// Server is assigning us OUR id
						msg >> nPlayerID;
						std::cout << "Assigned Client ID = " << nPlayerID << "\n";
						break;
					}

					case(GameMsg::Game_AddPlayer):
					{
						sPlayerDescription desc;
						msg >> desc;
						mapObjects.insert_or_assign(desc.nUniqueID, desc);

						if (desc.nUniqueID == nPlayerID)
						{
							// Now we exist in game world
							bWaitingForConnection = false;
						}
						break;
					}

					case(GameMsg::Game_RemovePlayer):
					{
						uint32_t nRemovalID = 0;
						msg >> nRemovalID;
						mapObjects.erase(nRemovalID);
						break;
					}

					case(GameMsg::Game_UpdatePlayer):
					{
						sPlayerDescription desc;
						msg >> desc;
						mapObjects.insert_or_assign(desc.nUniqueID, desc);
						break;
					}

					}
				}
			}
			if (bWaitingForConnection)
			{
				Clear(olc::DARK_BLUE);
				DrawString({ 10,10 }, "Waiting To Connect...", olc::WHITE);
				return true;
			}


			
			// Labmda function to convert "world" coordinate into screen space
			auto ToScreen = [&](int x, int y)
			{			
				return olc::vi2d
				{
					(vOrigin.x * vTileSize.x) + (x - y) * (vTileSize.x / 2) + viewOffset.x,
					(vOrigin.y * vTileSize.y) + (x + y) * (vTileSize.y / 2) + viewOffset.y
				};
			};

			auto ToScreenFloat = [&](float x, float y)
			{			
				return olc::vf2d
				{
					(vOrigin.x * vTileSize.x) + (x - y) * (vTileSize.x / 2) + viewOffset.x,
					(vOrigin.y * vTileSize.y) + (x + y) * (vTileSize.y / 2) + viewOffset.y
				};
			};

			// User Input
			// if (GetKey(olc::Key::W).bHeld) viewOffset += { 0, +1 };
			// if (GetKey(olc::Key::S).bHeld) viewOffset += { 0, -1 };
			// if (GetKey(olc::Key::A).bHeld) viewOffset += { +1, 0 };
			// if (GetKey(olc::Key::D).bHeld) viewOffset += { -1, 0 };

			mapObjects[nPlayerID].vVel = { 0.0f, 0.0f };
			if (GetKey(olc::Key::W).bHeld) mapObjects[nPlayerID].vVel += { -2, -2 };
			if (GetKey(olc::Key::S).bHeld) mapObjects[nPlayerID].vVel += { +2, +2 };
			if (GetKey(olc::Key::A).bHeld) mapObjects[nPlayerID].vVel += { -2, +2 };
			if (GetKey(olc::Key::D).bHeld) mapObjects[nPlayerID].vVel += { +2, -2 };


			// Render Layer 0 - DEBUG
			Clear(olc::BLANK);

			// Render Layer 1 - World
			SetDrawTarget(worldLayer);
			// WORLD DRAWING CRITICAL SECTION
			for (int y = 0; y < map->mapSize_y; y++)
			{
				for (int x = 0; x < map->mapSize_x; x++)
				{
					olc::vi2d vWorld = ToScreen(x, y);
					SG::world::SGTile tile = *tiles[map->pWorld[(y * (map->mapSize_x)) + x]];
					olc::vi2d pos = {tile.ox, tile.oy};
					olc::vi2d size = {tile.w, tile.h};
					if (tile.h == tile.tileSize_y * 2) 
					{
						vWorld.y -= vTileSize.y;
					}
					DrawPartialDecal(vWorld, map->decal, pos, size);
				}
			}

			EnableLayer(worldLayer, true);
			SetDrawTarget(nullptr);


			// // Render Layer 2 - GameObjects
			// SetDrawTarget(gameObjLayer);
			// // GAME OBJECT DRAWING CRITICAL SECTION
			// Clear(olc::BLANK);
			// EnableLayer(gameObjLayer, true);

			// // Render Layer 3 - Players
			// SetDrawTarget(playerObjLayer);
			// PLAYER DRAWING CRITICAL SECTION
			// Update objects locally
			for (auto& object : mapObjects)
			{
				// Where will object be worst case?
				olc::vf2d vPotentialPosition = object.second.vPos + object.second.vVel * fElapsedTime;
				object.second.vPos = vPotentialPosition;
				olc::vi2d vWorld = ToScreenFloat(object.second.vPos.x, object.second.vPos.y);

				player->getSpritePos(object.second.vVel);
				olc::vi2d size = {40, 40};
				DrawPartialDecal(vWorld, player->decal, player->currentSpritPos, size);

				DrawString(4, 4, "player (vel)   : " + std::to_string(object.second.vVel.x) + ", " + std::to_string(object.second.vVel.y), olc::WHITE);
				DrawString(4, 14, "player(world)   : " + std::to_string(vWorld.x) + ", " + std::to_string(vWorld.y), olc::WHITE);
			}
			// EnableLayer(playerObjLayer, true);

			// // Render Layer 3 - Interfaces
			// SetDrawTarget(interfaceLayer);
			// // INTERFACE DRAWING CRITICAL SECTION

			// EnableLayer(interfaceLayer, true);
			

			SetDrawTarget(nullptr);

			// Send player description
			olc::net::message<GameMsg> msg;
			msg.header.id = GameMsg::Game_UpdatePlayer;
			msg << mapObjects[nPlayerID];
			Send(msg);

			DrawString(4, 24, "player (id)   : " + std::to_string(mapObjects[nPlayerID].vPos.x) + ", " + std::to_string(mapObjects[nPlayerID].vPos.y), olc::WHITE);
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