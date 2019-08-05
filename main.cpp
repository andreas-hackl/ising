#include <iostream>
#include <fstream>
#include <vector>

#include <stdio.h>
#include <gsl/gsl_rng.h>
#include "spingrid.h"
#include "measurements.h"
#include "metropolis.h"


using namespace std;

const int J = 1;

// write measuresments into a file

void write_in_data(Measurements &measure, string name)
{
	vector<double> energies = measure.get_energy();
	vector<double> magnetization = measure.get_magnetization();
	ofstream file(name);
	for (int i = 0; i < energies.size(); ++i)
	{
		file << i+1 << "\t" << energies[i] << "\t" << magnetization[i] << endl;
	}
	file.close();
}



int main()
{

	//										//
	// Include the GNU Scientific Library 	//
	//										//
	
	gsl_rng *rng;
	
	rng = gsl_rng_alloc(gsl_rng_mt19937);
	
	//long seed = time(NULL);
	long seed = 1559040693;
	gsl_rng_set(rng, seed);
	
	cout << "seed: " << seed << endl;
	
	//										//
	//////////////////////////////////////////
	//										//
	
	
	
	// Define important variables:
	
	int n_x = 64;
	int n_y = n_x;

	int dim = 2;
	
	Spingrid<int> Lattice(dim, n_x, n_y);
	
	vector<int> size = Lattice.get_size();
	cout << "Lattice size: " << endl;
	cout << "n_x = " << size[0] << endl;
	cout << "n_y = " << size[1] << endl;
	
	cout << "x = " << 0 << endl;
	cout << "y = " << 9 << endl;

	cout << "index = " << p2i(0, 9, size[0], size[1]);
	Lattice.print_neighbors();
	cout << "Initialize a cold start with all spins in +1 direction" << endl;
	Lattice.init_cold(1);

	Measurements measure;

	measure = metropolis::metropolis(Lattice, rng, J, 2.0);

	write_in_data(measure, "T20.txt");
	return 0;
	
}

