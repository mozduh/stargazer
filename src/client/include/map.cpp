#include "../../shared/olcPixelGameEngine.h"
#include "../../shared/olcUTIL_DataFile.h"
#include "map.h"
#include <string>


SG::world::SGMap::SGMap(std::string mapName) 
{
    // load sprites for map
    std::string spritePath = "../assets/sprites/" + mapName + ".png";
    spriteSheet = new olc::Sprite(spritePath);

    olc::utils::datafile mapFile;
    std::string dataFilePath = "../assets/maps/" + mapName + ".map";

    if(olc::utils::datafile::Read(mapFile, dataFilePath))
    {
        
        // get map meta data
        name = mapFile["map"]["name"].GetString();
        mapSize_x = mapFile["map"]["mapSize_x"].GetInt();
        mapSize_y = mapFile["map"]["mapSize_y"].GetInt();
        
        // deserialize tileMap
        int tileMapCount = mapFile["map"]["tileMap"].GetValueCount();
        pWorld = new int[mapSize_x * mapSize_y]{ 0 };
        for (int i = 0; i < tileMapCount; i++) 
        {
            pWorld[i] = mapFile["map"]["tileMap"].GetInt(i);
        }

        // get tiles that are used in map
        tileCount = mapFile["map"]["tilesUsed"].GetValueCount();
        tiles = new std::string[tileCount] { };
        for (int i = 0; i < tileCount; i++)
        {
            tiles[i] = mapFile["map"]["tilesUsed"].GetString(i);
        }

    }
    else
    {
        std::cout << "Error Reading " + mapName + " file" << std::endl;
        // TODO -> Load unknown tile so that the map can still reference to a tile
    }
}