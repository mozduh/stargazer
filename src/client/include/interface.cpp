#include "../../shared/olcPixelGameEngine.h"
#include "./interface.h"
#include <string>

SG::ui::InterfaceController::InterfaceController()
{
    showInterface = true;
    showEscapeMenu = false;
}

void SG::ui::InterfaceController::drawEscapeMenu(olc::PixelGameEngine *ge)
{
    ge->DrawString(4, 34, "hello", olc::WHITE);
}

void SG::ui::InterfaceController::drawInterface(olc::PixelGameEngine *ge)
{
    if (showInterface)
    {
        if (showEscapeMenu)
            drawEscapeMenu(ge);

    }
}