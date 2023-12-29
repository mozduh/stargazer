#include "../../../shared/olcPixelGameEngine.h"
#include "../../../shared/olcUTIL_DataFile.h"
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
        ox = tileFile["tile"]["sheet_ox"].GetInt();
        oy = tileFile["tile"]["sheet_oy"].GetInt();
        w = tileFile["tile"]["sheet_wm"].GetInt();
        h = tileFile["tile"]["sheet_hm"].GetInt();
    }
    else
    {
        std::cout << "Error Reading " + tileName + " file" << std::endl;
        // TODO -> Load unknown tile so that the map can still reference to a tile
    }
}