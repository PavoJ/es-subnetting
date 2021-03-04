#pragma once

#include<cstdint>
#include<string>

namespace pavoLibs{ namespace networking{
    class IPv4Address;
    
    typedef IPv4Address NetMask;

    class IPv4Address{
    protected:
        uint32_t ipB;// ip in binario
    public:
        IPv4Address();
        IPv4Address(uint32_t ipB);
        ~IPv4Address();

        uint32_t& getBytes();
        void setBytes(uint32_t ip);

        std::string& toString();

        IPv4Address& operator&(IPv4Address& operand);

        static short getCIDR(NetMask n);
        static NetMask& fromCIDR(short s);
        static IPv4Address& parseString(std::string str);
    };

    struct IPv4N{
        IPv4N();
        IPv4N(IPv4Address ip, NetMask nm);
        std::string inspect();
        IPv4N& ipRete();
        IPv4Address& getBroadcast();
        
        IPv4Address ip;
        NetMask nm;
    };
}}

std::ostream& operator<<(std::ostream& stream, pavoLibs::networking::IPv4Address& ip);
std::ostream& operator<<(std::ostream& stream, pavoLibs::networking::IPv4N& address);