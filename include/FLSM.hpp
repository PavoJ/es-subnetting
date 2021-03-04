#pragma once

#include<IPv4Address.hpp>
#include<LinkedList.hpp>

namespace pavoLibs{ namespace networking{

    struct FLSM_results{
        IPv4N address;// ip della sottorete
        IPv4N nextIp;// ip della sottorete successiva
        IPv4Address broadcast;// indirizzo di broadcast
        IPv4Address ipRange[2];// range degli host della sottorete
        short magic_number;
        short N,H,S;
        short CIDR;
    };

    class FLSM{
        protected:
            IPv4N address;// ip/netmask di riferimento
            NetMask startMask; //netmask di partenza
            int nHosts;// numero host
            short nSNetworks;// numero sotto reti

            LinkedList<FLSM_results> results;
            void solve();
        public:
            FLSM(IPv4N address, short nSNetworks);
            FLSM(IPv4N address, short nSNetworks, int nHosts);

            int getNHosts();
            LinkedList<FLSM_results>& getResults();
    };

}}

std::ostream& operator<<(std::ostream& stream, pavoLibs::networking::FLSM& flsm);
std::ostream& operator<<(std::ostream& stream, pavoLibs::networking::FLSM_results& r);