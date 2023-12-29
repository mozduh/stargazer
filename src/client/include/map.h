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
                olc::vi2d vMapSize;
                
                // Sprite that holds all sprites that pertain to the map
                olc::Sprite *spriteSheet;

                // Pointer to create 2D world array
                int *pWorld;  
        };
    }
}