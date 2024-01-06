
namespace SG
{
    namespace net
    {
        class NetworkController : olc::net::client_interface<GameMsg>
        {
            public:
                NetworkController();

            public:
                std::unordered_map<uint32_t, sPlayerDescription> mapObjects;
                uint32_t nPlayerID = 0;
                sPlayerDescription descPlayer;
                bool bWaitingForConnection = true;

            public:
                bool ConnectToServer();
                bool ProcessInput();
                bool ProcessOutput();
        };
    }
}