namespace SG 
{
    namespace world 
    {
        class Player
        {
            public:
                Player();

            public:
                // Sprite that holds all sprites that pertain to the map
                olc::Sprite *spriteSheet;
                olc::Decal *decal;


                // used to draw out from sprite sheet with 4 corners
                int32_t ox;
                int32_t oy;
                int32_t w;
                int32_t h;
        };
    }
}