#include "../../shared/olcPixelGameEngine.h"
#include "../../shared/olcUTIL_DataFile.h"
#include "map.h"
#include <string>


SG::world::SGMap::SGMap(std::string mapName) 
{
    olc::utils::datafile mapFile;
    std::string dataFilePath = "../assets/maps/" + mapName + ".map";

    if(olc::utils::datafile::Read(mapFile, dataFilePath))
    {

    }
    else
    {
        std::cout << "Error Reading " + mapName + " file" << std::endl;
        // TODO -> Load unknown tile so that the map can still reference to a tile
    }
}