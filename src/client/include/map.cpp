#include "../../../shared/olcPixelGameEngine.h"
#include "map.h"
#include <unordered_map>


SG::map::SGTile::SGTile(olc::vi2d tileSize, int32_t mox, int32_t moy, int32_t mw, int32_t mh )
{
    vTileSize = tileSize;
    ox = tileSize.x * mox;
    oy = tileSize.y * moy;
    w = tileSize.x;
    h = tileSize.y * mh;
}

SG::map::SGMap::SGMap(olc::vi2d mapSize) 
{
    vMapSize = mapSize;

    // Load sprites used in demonstration
    sprIsom = new olc::Sprite("../assets/isometric_demo.png");

    // Create empty world
    pWorld = new int[vMapSize.x * vMapSize.y]{ 0 };
}

// namespace SG 
// {
//     namespace map 
//     {
//         class SGMap
//         {
//             public:
//                 SGMap()
//                 {
                    // // Load sprites used in demonstration
                    // sprIsom = new olc::Sprite("assets/isometric_demo.png");

                    // // Create empty world
                    // pWorld = new int[vMapSize.x * vMapSize.y]{ 0 };

                    // // create tiles and map them to ints
                    // umap[0] = sand;
//                 }
            
//             private:
//                // Number of tiles in map
//                 olc::vi2d vMapSize = { 14, 10 };

//                 // Sprite that holds all imagery
//                 olc::Sprite *sprIsom = nullptr;

//                 // example tile
//                 SG::map::SGTile sand = SG::map::SGTile(2, 1, 1, 2);

//                 // Pointer to create 2D world array
//                 int *pWorld = nullptr;

//                 unordered_map<int, SG::map::SGTile> umap; 
                

//             public:

//         };

//         class SGTile
//         {
//             public:
//                 SGTile(int32_t mox, int32_t moy, int32_t mh, int32_t mw )
//                 {
                    // ox = vTileSize.x * mox;
                    // oy = vTileSize.y * moy;
                    // w = vTileSize.x * mw;
                    // h = vTileSize.y * mh

//                 }

//             private:

//                 int tileID = 0;

//                 // tile size
//                 olc::vi2d vTileSize = { 40, 20 };

//                 // used to draw out from sprite sheet with 4 corners
//                 int32_t ox;
//                 int32_t oy;
//                 int32_t w;
//                 int32_t h;

//             public:

            
//         };
//     }
// }