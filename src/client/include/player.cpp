#include "../../shared/olcPixelGameEngine.h"
#include "player.h"


SG::world::Player::Player() 
{
    // load sprites for map
    std::string spritePath = "../assets/sprites/player.png";
    spriteSheet = new olc::Sprite(spritePath);
    decal = new olc::Decal(spriteSheet);

    ox = 0;
    oy = 0;
    w = 40;
    h = 40;

}