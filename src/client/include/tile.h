namespace SG 
{
    namespace world 
    {
        class SGTile
        {
            public:
                SGTile(std::string tileName);

            public:
                // bool flags
                bool isBoundary = false;
                bool isInteractive = false;

                // used to draw out from sprite sheet with 4 corners
                int32_t ox;
                int32_t oy;
                int32_t w;
                int32_t h;
        };
    }
}