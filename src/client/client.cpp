#include "../shared/common.h"
#include "./include/map.h"
#include "./include/tile.h"
#include "./include/player.h"
#include "./include/network.h"
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

		// current Map
		SG::world::SGMap *map;

		// Tiles TODO change to vector or array
		SG::world::SGTile **tiles;

		// variables for world rendering
		olc::vi2d vTileSize = { 40, 20 };
		olc::vi2d vOrigin = { 5, 1 };
		olc::vi2d viewOffset = { 0, 0 };

	private:
		std::unordered_map<uint32_t, SG::world::Player*> playerObjects;
		std::unordered_map<uint32_t, sPlayerDescription> mapObjects;
		uint32_t nPlayerID = 0;
		sPlayerDescription descPlayer;
		bool bWaitingForConnection = true;

	private:
		SG::net::NetworkController nc;


	public:
		bool OnUserCreate() override
		{
			// Create Drawing Layers
			interfaceLayer = CreateLayer();
			playerObjLayer = CreateLayer();
			gameObjLayer = CreateLayer();
			worldLayer = CreateLayer();
			SetDrawTarget(nullptr); // set to debug layer
			Clear(olc::BLANK);

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
						playerObjects.insert_or_assign(desc.nUniqueID, new SG::world::Player());
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
						playerObjects.erase(nRemovalID);
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
				SetDrawTarget(interfaceLayer);
				Clear(olc::DARK_BLUE);
				DrawString({ 10,10 }, "Waiting To Connect...", olc::WHITE);
				EnableLayer(interfaceLayer, true);
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
			// Clear(olc::BLANK);
			// this is done on create

			// Render Layer 1 - Interfaces
			SetDrawTarget(interfaceLayer);
			Clear(olc::BLANK);
			// INTERFACE DRAWING CRITICAL SECTION START //
			// DrawString(4, 4, "player (vel)   : " + std::to_string(object.second.vVel.x) + ", " + std::to_string(object.second.vVel.y), olc::WHITE);
			// DrawString(4, 14, "player(world)   : " + std::to_string(vWorld.x) + ", " + std::to_string(vWorld.y), olc::WHITE);
			DrawString(4, 24, "player (id)   : " + std::to_string(mapObjects[nPlayerID].vPos.x) + ", " + std::to_string(mapObjects[nPlayerID].vPos.y), olc::WHITE);
			// INTERFACE DRAWING CRITICAL SECTION END //
			EnableLayer(interfaceLayer, true);


			// Render Layer 2 - Players
			SetDrawTarget(playerObjLayer);
			Clear(olc::BLANK);
			// PLAYER DRAWING CRITICAL SECTION START //
			for (auto& object : mapObjects)
			{
				// Where will object be worst case?
				olc::vf2d vPotentialPosition = object.second.vPos + object.second.vVel * fElapsedTime;
				object.second.vPos = vPotentialPosition;
				olc::vi2d vWorld = ToScreenFloat(object.second.vPos.x, object.second.vPos.y);

				playerObjects[object.second.nUniqueID]->getSpritePos(object.second.vVel);
				olc::vi2d size = {40, 40};
				DrawPartialDecal(vWorld, playerObjects[object.second.nUniqueID]->decal, playerObjects[object.second.nUniqueID]->currentSpritPos, size);
				DrawString(4, 4, "player (vel)   : " + std::to_string(object.second.vVel.x) + ", " + std::to_string(object.second.vVel.y), olc::WHITE);
				DrawString(4, 14, "player(world)   : " + std::to_string(vWorld.x) + ", " + std::to_string(vWorld.y), olc::WHITE);
			}
			// PLAYER DRAWING CRITICAL SECTION END //
			EnableLayer(playerObjLayer, true);


			// Render Layer 3 - GameObjects
			SetDrawTarget(gameObjLayer);
			Clear(olc::BLANK);
			// GAME OBJECT DRAWING CRITICAL SECTION START //

			// GAME OBJECT DRAWING CRITICAL SECTION END //
			EnableLayer(gameObjLayer, true);

			// Render Layer 4 - World
			SetDrawTarget(worldLayer);
			Clear(olc::BLANK);
			// WORLD DRAWING CRITICAL SECTION START //
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
			// WORLD DRAWING CRITIAL SECTION END //
			EnableLayer(worldLayer, true);


			// set back to default layer
			// SetDrawTarget(nullptr);

			// NETWORK CRITICAL SECTION START //
			// Send player description
			olc::net::message<GameMsg> msg;
			msg.header.id = GameMsg::Game_UpdatePlayer;
			msg << mapObjects[nPlayerID];
			Send(msg);
			// NETWORK CRITICAL SECTION END //

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