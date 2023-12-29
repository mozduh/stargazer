#include "../../shared/olcPixelGameEngine.h"
#include "../../shared/olcUTIL_DataFile.h"
#include "tile.h"
#include <string>


SG::world::SGTile::SGTile(std::string tileName)
{
    olc::utils::datafile tileFile;
    std::string dataFilePath = "../assets/tiles/" + tileName + ".tile";

    if(olc::utils::datafile::Read(tileFile, dataFilePath))
    {
        isBoundary = tileFile["tile"]["isBoundary"].GetInt();
        isInteractive = tileFile["tile"]["isInteractive"].GetInt();
        ox = tileFile["tile"]["sheet_ox"].GetInt() * tileSize_x;
        oy = tileFile["tile"]["sheet_oy"].GetInt() * tileSize_y;
        w = tileFile["tile"]["sheet_wm"].GetInt() * tileSize_x;
        h = tileFile["tile"]["sheet_hm"].GetInt() * tileSize_y;
    }
    else
    {
        std::cout << "Error Reading " + tileName + " file" << std::endl;
        // TODO -> Load unknown tile so that the map can still reference to a tile
    }
}