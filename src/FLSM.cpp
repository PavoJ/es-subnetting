#include<FLSM.hpp>
#include<LinkedList.hpp>
#include"LinkedList.cpp"
#include<cmath>

namespace pavoLibs{ namespace networking{

    FLSM::FLSM(IPv4N address, short nSNetworks) : address(address), nSNetworks(nSNetworks), startMask(address.nm) {
        nHosts = pow(2.f, (32-ceil(log2(nSNetworks)))-IPv4Address::getCIDR(startMask));
        solve();
    }
    FLSM::FLSM(IPv4N address, short nSNetworks, int nHosts) : address(address), nHosts(nHosts), nSNetworks(nSNetworks), startMask(address.nm) 
    { solve(); }
    
    void FLSM::solve(){
        for(int i=0; i<nSNetworks && nHosts>2; i++)
        {
            FLSM_results r;

            r.H = ceil(log2(nHosts));
            r.N = NetMask::getCIDR(startMask);
            r.S = 32-r.N-r.H;
            
            r.magic_number = pow(2.f, r.H-(r.H/8)*8);
            uint32_t Amagic_number = pow(2.f, r.H);// magic number assoluto

            r.CIDR = r.N+r.S;
            NetMask newNM = IPv4Address::fromCIDR(r.CIDR);
            r.address = address.ipRete();
            r.address.nm = newNM;
            r.nextIp.ip = IPv4Address(address.ipRete().ip.getBytes()+Amagic_number);
            r.nextIp.nm = newNM;
            address = r.nextIp;
            
            r.broadcast = r.address.getBroadcast();
            r.ipRange[0] = IPv4Address(r.address.ip.getBytes()+1);
            r.ipRange[1] = IPv4Address(r.nextIp.ip.getBytes()-2);

            results.push(r);
        }
    }

    int FLSM::getNHosts() { return nHosts; }
    LinkedList<FLSM_results>& FLSM::getResults(){ return results; }

}}

std::ostream& operator<<(std::ostream& stream, pavoLibs::networking::FLSM& flsm){
    pavoLibs::LinkedList<pavoLibs::networking::FLSM_results>& res = flsm.getResults();
    
    for(int i=0; i<res.length(); i++){
        stream << res[i];
        if(i+1!=res.length()) stream << std::endl << std::endl;
    }

    return stream;
}

std::ostream& operator<<(std::ostream& stream, pavoLibs::networking::FLSM_results& r){
    stream << "indirizzo:" << r.address << std::endl;
    stream << "netmask: " << r.address.nm << std::endl;
    stream << "indirizzo broadcast:" << r.broadcast << std::endl;
    stream << "range da " << r.ipRange[0] << " a " << r.ipRange[1] << std::endl;
    stream << "magic number:"<< r.magic_number << std::endl;
    stream << "N:" << r.N << " H:" << r.H << " S:" << r.S;

    return stream;
}