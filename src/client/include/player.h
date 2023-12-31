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

                olc::vi2d currentSpritPos;
                olc::vi2d size;

                std::chrono::high_resolution_clock::time_point walkAnimeTimer;

                // used to draw out from sprite sheet with 4 corners
                int32_t ox;
                int32_t oy;
                int32_t w;
                int32_t h;

            public:
                void getSpritePos(olc::vf2d vel);
        };
    }
}