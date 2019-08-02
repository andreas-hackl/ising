#include <iostream>
#include <vector>


#include "measurements.h"


Measurements::Measurements()
{
    energies = std::vector<double> energies,
    magnetizations = std::vector<double> magnetizations;
}

Measurements::append_data(double energy, double magnetization)
{
    energies.push_back(energy);
    magnetizations.push_back(magnetization);

}