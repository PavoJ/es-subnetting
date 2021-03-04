#pragma once

#include<iostream>
#include<IPv4Address.hpp>

namespace pavoLibs{ namespace networking {
    class Esercizi{
    private:
        // generates an ip, used by the exercises
        static IPv4N& generateAddress();
    public:
        // randomly generates and displays information about an ip/nm pair
        static void networkAnalysis(std::ostream& stream, int quantity);
        // like networkAnalysis, but it displays more in-depth information
        static void deepNetworkAnalysis(std::ostream& stream, int quantity);
        // randomly generates ips and subnets them on BitSnets bits (S=BitSnets)
        static void predeterminedFLSM(std::ostream& stream, int quantity, short BitSnets);
        // randomly generates and solves FLSM exercises
        static void genericFLSM(std::ostream& stream, int quantity);
        // randomly generates and solves VLSM exercises
        static void genericVLSM(std::ostream& stream, int quantity);
    };
}}