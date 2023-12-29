
namespace SG 
{
    namespace world 
    {
        class SGTile
        {
            public:
                SGTile(olc::vi2d tileSize, int32_t mox, int32_t moy, int32_t mh, int32_t mw );

            public:
                // tile size
                olc::vi2d vTileSize;

                // used to draw out from sprite sheet with 4 corners
                int32_t ox;
                int32_t oy;
                int32_t w;
                int32_t h;
        };
    }
}