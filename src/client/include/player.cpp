#include "../../shared/olcPixelGameEngine.h"
#include "player.h"


SG::world::Player::Player() 
{
    // load sprites for map
    std::string spritePath = "../assets/sprites/player.png";
    spriteSheet = new olc::Sprite(spritePath);
    decal = new olc::Decal(spriteSheet);

    currentSpritPos = {0, 0};
    size = {40, 40};

    ox = 0;
    oy = 0;
    w = 40;
    h = 40;

}

olc::vi2d SG::world::Player::getSpritePos(olc::vf2d vel)
{
    // if (GetKey(olc::Key::W).bHeld) mapObjects[nPlayerID].vVel += { -2, -2 };
    // if (GetKey(olc::Key::S).bHeld) mapObjects[nPlayerID].vVel += { +2, +2 };
    // if (GetKey(olc::Key::A).bHeld) mapObjects[nPlayerID].vVel += { -2, +2 };
    // if (GetKey(olc::Key::D).bHeld) mapObjects[nPlayerID].vVel += { +2, -2 };
    
    
    
    return { };

}