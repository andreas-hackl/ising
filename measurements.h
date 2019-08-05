#pragma once

#include <vector>

class Measurements
{
    public:
        Measurements();


        void append_data(double energy, double magnetization);
        std::vector<double> get_energy();
        std::vector<double> get_magnetization();


    private:
        std::vector<double> energies;
        std::vector<double> magnetizations; 

};