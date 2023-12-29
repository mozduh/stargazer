#include "../../../shared/olcPixelGameEngine.h"
#include "../../../shared/olcUTIL_DataFile.h"
#include "map.h"
#include <string>


SG::world::SGMap::SGMap(std::string mapName) 
{
    olc::utils::datafile tileFile;
    std::string dataFilePath = "../assets/maps/" + tileName + ".map";

    if(olc::utils::datafile::Read(tileFile, dataFilePath))
    {
        
    }
    else
    {
        std::cout << "Error Reading " + tileName + " file" << std::endl;
        // TODO -> Load unknown tile so that the map can still reference to a tile
    }
}