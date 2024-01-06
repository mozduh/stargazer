
namespace SG
{
    namespace ui {
        class InterfaceController
        {
            public:
                InterfaceController();
            
            public:
                bool showInterface;
                bool showEscapeMenu;

            public:
                void drawInterface(olc::PixelGameEngine *ge);
                void drawEscapeMenu(olc::PixelGameEngine *ge);
        };
    }
}