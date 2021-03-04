#include<LinkedList.hpp>
#include<FLSM.hpp>
#include<IPv4Address.hpp>

namespace pavoLibs{ namespace networking{
    class VLSM{
        protected:
            IPv4N address;
            NetMask startMask;
            LinkedList<short>& nHosts;
            short nSNetworks;

            LinkedList<FLSM*> results;
            void solve();
        public:
            VLSM(IPv4N address, LinkedList<short>& nHosts);
            LinkedList<FLSM*>& getResults();
    };
}}

std::ostream& operator<<(std::ostream& stream, pavoLibs::networking::VLSM& vlsm);