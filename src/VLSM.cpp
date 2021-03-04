#include<VLSM.hpp>
#include<FLSM.hpp>
#include<IPv4Address.hpp>
#include<LinkedList.hpp>
#include"LinkedList.cpp"

namespace pl = pavoLibs;
namespace pln = pl::networking;

namespace pavoLibs{ namespace networking{
    VLSM::VLSM(IPv4N address, LinkedList<short>& nHosts):address(address),startMask(address.nm),nHosts(nHosts),nSNetworks(nHosts.length()){
        this->nHosts.sort([](short v1, short v2)->bool{ return v1<v2; });
        solve();
    }

    void VLSM::solve(){
        int i=0, hAccumulated;// raggruppo più numeri di host uguali per un unico calcolo di FLSM 
        int hostsLen = nHosts.length();
        while(i<hostsLen){
            hAccumulated=1;
            while(i!=hostsLen-1 && nHosts[i]==nHosts[i+1]){  hAccumulated++; i++; }
            
            FLSM* calc = new FLSM(address, hAccumulated, nHosts[i]);
            results.push(calc);
            LinkedList<FLSM_results>& FLSMresults = calc->getResults();
            if(FLSMresults.length()!=0 && FLSMresults[hAccumulated-1].S>0) address = FLSMresults[hAccumulated-1].nextIp;
            else{
                results = LinkedList<FLSM*>();
                return;
            }

            i++;
        }
    }

    LinkedList<FLSM*>& VLSM::getResults(){ return results; }
}}

std::ostream& operator<<(std::ostream& stream, pavoLibs::networking::VLSM& vlsm){
    pavoLibs::LinkedList<pavoLibs::networking::FLSM*>& sll = vlsm.getResults();

    int len=sll.length();
    for(int i=0; i<len; i++){
        stream << *sll[i];
        if(i!=len-1) stream << std::endl << std::endl;
    }

    return stream;
}