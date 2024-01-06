#include "../../shared/olcPixelGameEngine.h"
#include "./interface.h"
#include "./controller.h"

SG::ui::GamePadController::GamePadController()
{

};

olc::vf2d SG::ui::GamePadController::processMovementInputs(olc::PixelGameEngine *ge)
{
    olc::vf2d vel = { 0.0f, 0.0f };
    if (ge->GetKey(olc::Key::W).bHeld) vel += { -2, -2 };
    if (ge->GetKey(olc::Key::S).bHeld) vel += { +2, +2 };
    if (ge->GetKey(olc::Key::A).bHeld) vel += { -2, +2 };
    if (ge->GetKey(olc::Key::D).bHeld) vel += { +2, -2 };
    return vel;
};

void SG::ui::GamePadController::processInterfaceInputs(olc::PixelGameEngine *ge, SG::ui::InterfaceController *ic)
{
    if (ge->GetKey(olc::Key::ESCAPE).bPressed) ic->showEscapeMenu = !ic->showEscapeMenu;
};