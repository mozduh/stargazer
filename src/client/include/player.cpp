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
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::seconds s;
    typedef std::chrono::duration<float> fsec;

    fsec duration;
    bool walking = false;

    if (vel.x == 0 && vel.y == 0)
    {
        currentSpritPos.x = 0;
        std::cout << "timer varible " << walkAnimeTimer << std::endl;
        walkAnimeTimer = std::chrono::high_resolution_clock::now();
        // don't change sprite, player is not moving
        return;
    }
    else
    {
        // start walking/running sprite
        duration = std::chrono::duration_cast<ms>(std::chrono::high_resolution_clock::now() - walkAnimeTimer);
        if (std::chrono::floor<s>(duration) == std::chrono::round<s>(duration)){
            // below half a second
            walking = false;
            currentSpritPos.x = 40;
        }
        else 
        {
            walking = true;
            currentSpritPos.x = 80;
        }


        auto floor = std::chrono::floor<s>(duration);
        auto round = std::chrono::round<s>(duration);
        std::cout << "round " << round << std::endl;
        std::cout << "floor  " << floor << std::endl;
        std::cout << "duration " << duration << std::endl;
        std::cout << "walking " << walking << std::endl;
    }

    // player is moving, find out the direction and set the current sprite postion properly
    if (vel.x == 0)
    {
        if (vel.y > 0)
        {
            // down left
            currentSpritPos.y = 40;
            return;
        }
        else 
        {
            // top right
            currentSpritPos.y = 200;
            return;
        }
    }
    if (vel.y == 0)
    {
        if (vel.x > 0)
        {
            // down right
            currentSpritPos.y = 280;
            return;
        }
        else
        {
            // top left
            currentSpritPos.y = 120;
            return;
        }
    }
    if (vel.x > 0 && vel.y > 0)
    {
        // down
        currentSpritPos.y = 0;
        return;
    }
    if (vel.x < 0 && vel.y < 0)
    {
        // up
        currentSpritPos.y = 160;
        return;
    }
    if (vel.x > 0 && vel.y < 0)
    {
        // right
        currentSpritPos.y = 240;
        return;
    }
    if (vel.x < 0 && vel.y > 0)
    {
        // left
        currentSpritPos.y = 80;
        return;
    }


    return;
}