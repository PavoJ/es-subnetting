#include<Exercises.hpp>
#include<cmath>
#include<FLSM.hpp>
#include<VLSM.hpp>
#include<LinkedList.hpp>
#include"LinkedList.cpp"

namespace pavoLibs{ namespace networking{

    IPv4N& Esercizi::generateAddress(){ return (*new IPv4N(IPv4Address(std::rand()%(uint32_t)~0), NetMask::fromCIDR(std::rand()%31+1)) ); }

    void Esercizi::networkAnalysis(std::ostream& stream, int quantity){
        for(int i=0; i<quantity; i++) stream << generateAddress().inspect() << std::endl << std::endl;
    }

    void Esercizi::deepNetworkAnalysis(std::ostream& stream, int quantity){
        for(int i=0; i<quantity; i++){
            
        }
    }

    void Esercizi::predeterminedFLSM(std::ostream& stream, int quantity, short BitSnets){
        int i=quantity;
        while(i>0){
            IPv4N& generatedAddress = generateAddress();
            short nSNetworks = BitSnets;
            FLSM esercizioFLSM(generatedAddress, 3, pow(2.f, (32-BitSnets) - IPv4Address::getCIDR(generatedAddress.nm)));
            
            if(esercizioFLSM.getResults().length()!=0) {
                stream << (quantity+1)-i << ")"  << "FLSM di " << generatedAddress << ": " <<  nSNetworks << " reti da " << esercizioFLSM.getNHosts()-3 << " host ciascuna" << std::endl << esercizioFLSM;
                stream << std::endl << std::endl;
            }else{
                i++;
            }
            i--;
        }
    }

    void Esercizi::genericFLSM(std::ostream& stream, int quantity){
        int i = quantity;
        while(i>0){
            IPv4N& generatedAddress = generateAddress();
            short nSNetworks = std::rand()%5+2;
            FLSM esercizioFLSM(generatedAddress, nSNetworks);
            
            if(esercizioFLSM.getResults().length()!=0) {
                stream << (quantity+1)-i << ")"  << "FLSM di " << generatedAddress << ": " <<  nSNetworks << " reti da " << esercizioFLSM.getNHosts()-3 << " host ciascuna" << std::endl << esercizioFLSM;
                stream << std::endl << std::endl;
            }else{
                i++;
            }
            i--;
        }
    }

    void Esercizi::genericVLSM(std::ostream& stream, int quantity){
        int i = quantity;
        while(i>0){
            IPv4N& generatedAddress = generateAddress();
            short listLen = std::rand()%5+2;
            LinkedList<short>* SNetList = new LinkedList<short>();

            int nHosts = pow(2.f, 32-NetMask::getCIDR(generatedAddress.nm));
            for(int l=0; l<listLen; l++) SNetList->push(std::rand()%nHosts+1);

            LinkedList<short> SNetListCopy(*SNetList);

            VLSM esercizioVLSM(generatedAddress, *SNetList);
            if(esercizioVLSM.getResults().length()!=0) {
                stream << 301-i << ")" << "VLSM di " << generatedAddress << ": " << listLen << " reti da ";
                for(int l=0; l<listLen; l++){
                    stream << SNetListCopy[l];
                    
                    if(l != listLen-1)  stream << ", ";
                    else                stream << " host ciascuna" << std::endl;
                }

                stream << esercizioVLSM;
                stream << std::endl << std::endl;
            }else i++;
            
            i--;
        }
    }
}}