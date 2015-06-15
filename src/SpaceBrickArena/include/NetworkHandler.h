#ifndef _NETWORKHANDLER_H_
#define _NETWORKHANDLER_H_

// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>
#include <TheBrick/TheBrick.h>
#include "include/INIReader.h"

// Declare namespace Game
namespace Game
{
    enum { MaxPlayers = 10, Delay = 10 };

    enum Packet {Join,Left,IAm,CJoin,Start,STick,CTick};

    /// @brief Struct which handles the Input one Player does
    ///
    struct InputData
    {
        unsigned char Player;
        bool Shoot;
        bool Thrust;
        unsigned char Spin;
        unsigned char MoveX;
        unsigned char MoveY;

    };
    /// @brief HeaderPacket, used to tell which Packet we got
    ///
    struct HeadPacket
    {
        Packet Type;
    };

    /// @brief Packet used when Data is received, this checks the Header
    ///
    struct ReceivePacket
    {
        HeadPacket Head;
        char* Buffer;
    };

    /// @brief Packet used to detect who left
    ///
    struct LeftPacket
    {
        HeadPacket Head;
        int Who;
    };

    /// @brief Packet for Inputs
    ///
    struct InputPacket
    {
        HeadPacket Head;
        int Frame;
        InputData Input;
    };

    /// @brief Packet for all Inputs
    ///
    struct InputsPacket
    {
        HeadPacket Head;
        int Players;
        int Frame;
        InputData Input[MaxPlayers]; //we send 
    };


    class CNetworkHandler
    {
    public:
        std::string m_IP;
        std::string m_Port;
        bool m_Host;
        int m_NetworkState;

        private:
            PuRe_Socket* m_pSocket;
        public:
            CNetworkHandler();
            ~CNetworkHandler();
    public:
        bool Listen();
        SOCKET Accept();
            void Connect();
            void Update(PuRe_IInput* a_pInput);
            int GetState();
            int GetSocket();
            long Receive(char* a_pBuffer, int a_Size, SOCKET a_pSender);
            void Send(char* a_pBuffer, int a_Size, SOCKET a_Receiver);
            void SendHost(char* a_pBuffer, int a_Size);
    };
}
#endif /* _NETWORKHANDLER_H_ */