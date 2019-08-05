#include <iostream>
#include <vector>


#include "measurements.h"


Measurements::Measurements()
{
    std::vector<double> energ;
    std::vector<double> magn;
    energies = energ;
    magnetizations = magn;
}

void Measurements::append_data(double energy, double magnetization)
{
    energies.push_back(energy);
    magnetizations.push_back(magnetization);

}

std::vector<double> Measurements::get_energy()
{
    return energies;
}

std::vector<double> Measurements::get_magnetization()
{
    return magnetizations;
}