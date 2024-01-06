
namespace SG
{
    namespace ui 
    {
        class GamePadController
        {
            public:
                GamePadController();

            public:
                olc::vf2d processMovementInputs(olc::PixelGameEngine *ge);
                void processInterfaceInputs(olc::PixelGameEngine *ge, SG::ui::InterfaceController *ic);
        };
    }
}