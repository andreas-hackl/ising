#pragma once

#include <vector>
#include "spingrid.h"
#include "measurements.h"


#include <stdio.h>
#include <gsl/gsl_rng.h>

const double k = 1.0;

namespace metropolis
{
    void sweep(Spingrid<int> &Lattice, std::vector<double> &Boltzman_values,  gsl_rng *rng, int J);
    Measurements metropolis(Spingrid<int> &Lattice, gsl_rng *rng, int J, double T);   
}