
namespace SG 
{
    namespace world 
    {
        class SGMap
        {
            public:
                SGMap(olc::vi2d mapSize);
            
            public:
               // Number of tiles in map
                olc::vi2d vMapSize;

                // Sprite that holds all imagery
                olc::Sprite *sprIsom;

                // Pointer to create 2D world array
                int *pWorld;  
        };
    }
}