#include "../../shared/olcPGEX_Network.h"
#include "../../shared/network_common.h"
#include <string>
#include "network.h"
#include <unordered_map>

SG::net::NetworkController::NetworkController()
{

};

bool SG::net::NetworkController::ConnectToServer()
{
    // Network Connect
    if (Connect("127.0.0.1", 60000))
    {
        return true;
    }
    return false;
};

bool SG::net::NetworkController::ProcessInput()
{
    // Check for incoming network messages
    if (IsConnected())
    {
        while (!Incoming().empty())
        {
            auto msg = Incoming().pop_front().msg;

            switch (msg.header.id)
            {
            case(GameMsg::Client_Accepted):
            {
                std::cout << "Server accepted client - you're in!\n";
                olc::net::message<GameMsg> msg;
                msg.header.id = GameMsg::Client_RegisterWithServer;
                descPlayer.vPos = { 3, 3 };
                msg << descPlayer;
                Send(msg);
                break;
            }

            case(GameMsg::Client_AssignID):
            {
                // Server is assigning us OUR id
                msg >> nPlayerID;
                std::cout << "Assigned Client ID = " << nPlayerID << "\n";
                break;
            }

            case(GameMsg::Game_AddPlayer):
            {
                sPlayerDescription desc;
                msg >> desc;
                // playerObjects.insert_or_assign(desc.nUniqueID, new SG::world::Player());
                mapObjects.insert_or_assign(desc.nUniqueID, desc);
                std::cout << "adding player" << std::endl;
                if (desc.nUniqueID == nPlayerID)
                {
                    std::cout << "setting it" << std::endl;

                    // Now we exist in game world
                    bWaitingForConnection = false;
                }
                break;
            }

            case(GameMsg::Game_RemovePlayer):
            {
                uint32_t nRemovalID = 0;
                msg >> nRemovalID;
                // playerObjects.erase(nRemovalID);
                mapObjects.erase(nRemovalID);
                break;
            }

            case(GameMsg::Game_UpdatePlayer):
            {
                sPlayerDescription desc;
                msg >> desc;
                mapObjects.insert_or_assign(desc.nUniqueID, desc);
                break;
            }

            }
        }
    }
    if (bWaitingForConnection)
    {
        return true;
    }

    return false;
};
                
bool SG::net::NetworkController::ProcessOutput()
{
    olc::net::message<GameMsg> msg;
    msg.header.id = GameMsg::Game_UpdatePlayer;
    msg << mapObjects[nPlayerID];
    Send(msg);
    return true;
};