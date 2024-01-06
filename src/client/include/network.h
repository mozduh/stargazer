
namespace SG
{
    namespace net
    {
        class NetworkController
        {
            public:
                NetworkController();

            public:
                olc::net::client_interface<GameMsg> ci;

            public:
                bool ConnectToServer(std::string domain, int port);
                bool ProcessInput();
                bool ProcessOutput();
        };
    }
}