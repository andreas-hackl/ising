#include <iostream>
#include <vector>
#include <gsl/gsl_rng.h>

#include "metropolis.h"
#include "measurements.h"

// Algorithm for one sweep in the metropolis algorim
void metropolis::sweep(Spingrid<int> &Lattice, vector<double> &Boltzman_values,  gsl_rng *rng, int J)
{
    double random_number;
    int boltzman_index = 0;
    int dE;
    int index;

    for (int k = 0; k < SpinGrid.size(); ++k)
    {
        index = gsl_rng_uniform_int(rng, Lattice.get_vol());
        dE = Lattice.spin_flip_energy(index, J);
        if (dE <= 0) Lattice.spin_flip(index);
        else
        {
            random_number = gsl_rng_uniform(rng);
            boltzman_index = dE/4 - 1;

            if (random_number <= Boltzman_values[boltzman_index])
            {
                Lattice.spin_flip(index);
            }
        }
    }
    
}

Measurements metropolis::metropolis(Spingrid<int> &Lattice, int n_x, int n_y, gsl_rng *rng, int J, double T)
{
        const int N_MC = 10000000;  // Number of sweeps for the Monte Carlo simulation
 
        Measurements measure;
        vector<double> Boltzman_values(2);
        double beta = 1/(k*T);

        double E;
        double M;


        for (int i = 0; i < 2; ++i)
        {
            Boltzman_values[i] = exp(-4*(i+1)*J*beta);
        }

        cout << "Starting metropolis:" << endl;

        
        for (int i = 0; i < 100; ++i) cout << "#";
        cout << endl;

        for (int i = 0; i < N_MC; ++i)
        {
            if (i%(N_MC/100) == N_MC/100 - 1) cout << "#" << flush;
            sweep(Lattice, Boltzman_values, rng, J);
            
            E = Lattice.get_energy(J);
            M = Lattice.get_magnetization();

            measure.append_data(E, M);
        }
        cout << endl;
    
        return measure;
    }