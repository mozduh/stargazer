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

void SG::world::Player::getSpritePos(olc::vf2d vel)
{
    // if (GetKey(olc::Key::W).bHeld) mapObjects[nPlayerID].vVel += { -2, -2 };
    // if (GetKey(olc::Key::S).bHeld) mapObjects[nPlayerID].vVel += { +2, +2 };
    // if (GetKey(olc::Key::A).bHeld) mapObjects[nPlayerID].vVel += { -2, +2 };
    // if (GetKey(olc::Key::D).bHeld) mapObjects[nPlayerID].vVel += { +2, -2 };
    // set currentSpritPos
    // default will be down
    // std::cout << "normal vector of vel: " << vel.norm() << std::endl;
    if (vel.x == 0 && vel.y == 0)
    {
        // don't change sprite, player is not moving
        return;
    }

    // player is moving, find out the direction and set the current sprite postion properly
    if (vel.x == 0)
    {
        if (vel.y > 0)
        {
            // down left
            currentSpritPos = { 0, 40 };
            return;
        }
        else 
        {
            // top right
            currentSpritPos = { 0, 200 };
            return;
        }
    }
    if (vel.y == 0)
    {
        if (vel.x > 0)
        {
            // down right
            currentSpritPos = { 0, 280 };
            return;
        }
        else
        {
            // top left
            currentSpritPos = { 0, 120 };
            return;
        }
    }
    if (vel.x > 0 && vel.y > 0)
    {
        // down
        currentSpritPos = { 0, 0 };
        return;
    }
    if (vel.x < 0 && vel.y < 0)
    {
        // up
        currentSpritPos = { 0, 160 };
        return;
    }
    if (vel.x > 0 && vel.y < 0)
    {
        // right
        currentSpritPos = { 0, 240 };
        return;
    }
    if (vel.x < 0 && vel.y > 0)
    {
        // left
        currentSpritPos = { 0, 80 };
        return;
    }


    return;
}