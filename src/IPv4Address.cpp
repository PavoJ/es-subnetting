#include<IPv4Address.hpp>
#include<vector>
#include<sstream>
#include<iostream>
#include<cmath>

namespace pavoLibs{ namespace networking{

    IPv4Address::IPv4Address():ipB(0) { }
    IPv4Address::IPv4Address(uint32_t ipB):ipB(ipB) { }
    IPv4Address::~IPv4Address(){ return; }

    uint32_t& IPv4Address::getBytes(){ return ipB; }
    void IPv4Address::setBytes(uint32_t ip) { ipB = ip; }

    std::string& IPv4Address::toString(){
        std::string& ret = *(new std::string());
        uint32_t ipB = this->ipB;
        uint8_t num = 0;

        for(int i=3; i>=0; i--){
            num = ipB>>i*8;
            ret += std::to_string(num);
            ipB -= num<<i*8;
            if(i!=0) ret+=".";
        }

        return ret;
    }

    IPv4Address& IPv4Address::operator&(IPv4Address& operand){
        return *(new IPv4Address(operand.getBytes() & this->getBytes()));
    }

    short IPv4Address::getCIDR(NetMask n){
        uint32_t nmB = n.getBytes();
        for(int i=0; i<32; i++) if(nmB & 1 << i) return 32-i;
        return 0;
    }

    NetMask& IPv4Address::fromCIDR(short s){
        uint32_t nm = 0;
        for(int i=0; i<s; i++) nm += 1 << 31-i;
        return *(new NetMask(nm));
    }

    IPv4Address& IPv4Address::parseString(std::string str){
        // https://stackoverflow.com/questions/19370078/split-the-string-on-dot-and-retrieve-each-values-from-it-in-c
        std::istringstream iss(str);
        std::string token = "";
        uint32_t ipB = 0;

        for(int i=3; i>=0; i--){
            std::getline(iss, token, '.');
            ipB += std::stoi(token) << i*8;
        }

        return *(new IPv4Address(ipB));
    }

    IPv4N::IPv4N() { }
    IPv4N::IPv4N(IPv4Address ip, NetMask nm): ip(ip),nm(nm){ }
    std::string IPv4N::inspect(){
        std::string ret = "";
        ret += "ip: " + ip.toString() + "\n";
        ret += "netmask: "+nm.toString()+"\n";
        ret += "Indirizzo di rete: "+this->ipRete().ip.toString()+"\n";
        ret += "Indirizzo di broadcast "+this->getBroadcast().toString()+"\n";
        ret += "Range ip per host da "+
            IPv4Address(this->ipRete().ip.getBytes()+1).toString()+" a "+
            IPv4Address(this->getBroadcast().getBytes()-1).toString();

        return ret;
    }
    IPv4N& IPv4N::ipRete(){ return *(new IPv4N(ip&nm, nm)); }
    IPv4Address& IPv4N::getBroadcast(){ return *(new IPv4Address(~nm.getBytes() | ip.getBytes())); }
}}

std::ostream& operator<<(std::ostream& stream, pavoLibs::networking::IPv4Address& ip){
    stream << ip.toString();
    return stream;
}


std::ostream& operator<<(std::ostream& stream, pavoLibs::networking::IPv4N& address){
    stream << address.ip << "/" << pavoLibs::networking::NetMask::getCIDR(address.nm);
    return stream;
}