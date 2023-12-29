#include "../../../shared/olcPixelGameEngine.h"

namespace SG 
{
    namespace map 
    {
        class SGMap
        {
            public:
                SGMap()
                {
                    // Load sprites used in demonstration
                    sprIsom = new olc::Sprite("assets/isometric_demo.png");

                    // Create empty world
                    pWorld = new int[vMapSize.x * vMapSize.y]{ 0 };
                }
            
            private:
               // Number of tiles in map
                olc::vi2d vMapSize = { 14, 10 };

                // Size of single tile graphic
                olc::vi2d vTileSize = { 40, 20 };

                // Where to place tile (0,0) on screen (in tile size steps)
                olc::vi2d vOrigin = { 5, 1 };

                // Sprite that holds all imagery
                olc::Sprite *sprIsom = nullptr;

                // Pointer to create 2D world array
                int *pWorld = nullptr;
            
            public:

        };

        class SGTile
        {
            public:
                SGTile(olc::Sprite *sprIsom)
                {
                    spriteRef = sprIsom;
                }

            private:
                olc::Sprite *spriteRef = nullptr;
                olc::vi2d vTileSize = { 40, 20 };

                // used to draw out from sprite sheet with 4 corners
                int32_t ox;
                int32_t oy;
                int32_t w;
                int32_t h;

            public:
                void drawTile()
                {

                }
            
        };
    }
}