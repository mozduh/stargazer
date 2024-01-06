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

            public:
                void getSpritePos(olc::vf2d vel);
        };
    }
}