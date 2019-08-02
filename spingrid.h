#pragma once


#include <vector>

#include <stdio.h>
#include <gsl/gsl_rng.h>


std::vector<int> i2p(int index, int n_x, int n_y);
int p2i(int x, int y, int n_x, int n_y);
std::vector<int> get_neighbors_2d(int n_x, int n_y);

template <typename T>
class Spingrid
{
    public:

        // definition of the constructor

        Spingrid<T>(int dim, int n);
        Spingrid<T>(int dim, int n_x, int n_y);

        // definition of the methods

        std::vector<int> get_size();
        int get_vol();


        void init_cold(T value); 
        void init_hot(gsl_rng *rng, double p);
        void print_lattice();

        void spin_flip(int index);
        int spin_flip_energy(int index, int J);

        double get_magnetization();
        double get_energy(int J);

    private:
        std::vector<int> size;
        int vol;
        std::vector<T> lattice;
        std::vector<int> neighbors;
};

