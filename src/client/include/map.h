namespace SG 
{
    namespace world 
    {
        class SGMap
        {
            public:
                SGMap(std::string mapName);
            
            public:
                std::string name;

               // Number of tiles in map
                int mapSize_x;
                int mapSize_y;
                
                // Sprite that holds all sprites that pertain to the map
                olc::Sprite *spriteSheet;

                // Tiles used
                std::string *tiles;

                // Pointer to create 2D world array thats based in world coordinates
                int *pWorld;
        };
    }
}