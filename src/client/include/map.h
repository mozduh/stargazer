#include <string>

namespace SG 
{
    namespace world 
    {
        class SGMap
        {
            public:
                SGMap(std::string mapName);
            
            public:
               // Number of tiles in map
                int mapSize_x;
                int mapSize_y;
                
                // Sprite that holds all sprites that pertain to the map
                std::string spriteSheetName;
                olc::Sprite *spriteSheet;

                // Pointer to create 2D world array thats based in world coordinates
                int pWorld[0][0];
        };
    }
}