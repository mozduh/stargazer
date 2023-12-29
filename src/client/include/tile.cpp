#include "../../../shared/olcPixelGameEngine.h"
#include "tile.h"

SG::world::SGTile::SGTile(olc::vi2d tileSize, int32_t mox, int32_t moy, int32_t mw, int32_t mh )
{
    vTileSize = tileSize;
    ox = tileSize.x * mox;
    oy = tileSize.y * moy;
    w = tileSize.x;
    h = tileSize.y * mh;
}