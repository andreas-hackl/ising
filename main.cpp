#include <iostream>
#include <fstream>
#include <vector>

#include <stdio.h>
#include <gsl/gsl_rng.h>
#include "spingrid.h"


using namespace std;

// write measuresments into a file
/*
void write_in_data(measurements measure, double T, int n_x, int n_y, string name)
{
	vector<int> energies = measure.energies;
	vector<int> magnetization = measure.magnetizations;
	int V = n_x * n_y;
	ofstream file(name);
	for (int i = 0; i < energies.size(); ++i)
	{
		file << i+1 << "\t" << static_cast<double>(energies[i])/V << "\t" << static_cast<double>(magnetization[i])/V << endl;
	}
	file.close();
}
*/


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
	
	int n_x = 10;
	int n_y = n_x;

	int dim = 2;

	int J = 1;
	
	
	Spingrid<int> Lattice(dim, n_x, n_y);
	
	vector<int> size = Lattice.get_size();
	cout << "n_x = " << size[0] << endl;
	cout << "n_y = " << size[1] << endl;

	Lattice.init_hot(rng, 0.5);

	Lattice.print_lattice();

	cout << Lattice.get_magnetization() << endl;

	Lattice.spin_flip(1);

	Lattice.print_lattice();

	cout << Lattice.get_magnetization() << endl;
	cout << Lattice.get_energy(J) << endl;
	return 0;
	
}

