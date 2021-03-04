#include<Exercises.hpp>
#include<fstream>

namespace pl = pavoLibs;
namespace pln = pl::networking;


int main(int argc, char** argv){
    srand((int) time(0));
    
    int nEs = 5;
    std::ofstream *compiti = new std::ofstream[nEs];
    std::string esFile[] = {"esercizio1.txt", "esercizio3.txt", "esercizio4.txt", "esercizio5.txt", "esercizio6.txt"};

    int esQnt = 300;
    for(int es=0; es<nEs; es++){ 
        compiti[es].open(esFile[es], std::ios::out);

        if(compiti[es].is_open()){
            switch(es){
            case 0:// esercizio 1
                pln::Esercizi::networkAnalysis(compiti[es], esQnt);
                break;
            
            case 1:// esercizio 3
                pln::Esercizi::predeterminedFLSM(compiti[es], esQnt, 3);
                break;

            case 2:// esercizio 4
                pln::Esercizi::genericFLSM(compiti[es], esQnt);
                break;

            case 3:// esercizio 5
                pln::Esercizi::genericVLSM(compiti[es], esQnt);
                break;

            case 4:// esercizio 6
                pln::Esercizi::deepNetworkAnalysis(compiti[es], esQnt);
                break;
            }
            compiti[es].close();
        }
    }
    
    return 0;
}
