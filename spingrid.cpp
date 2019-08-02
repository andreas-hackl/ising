#include <iostream>
#include <fstream>
#include <vector>

#include <stdio.h>
#include <gsl/gsl_rng.h>

#include "spingrid.h"

std::vector<int> i2p(int index, int n_x, int n_y)
{
    std::vector<int> pos(2);

    pos[0] = int(index/n_x);
    pos[1] = index%n_x;

    return pos;
}

int p2i(int x, int y, int n_x, int n_y)
{
    int index = y * n_x + x; 
    return index;
}


std::vector<int> get_neighbors_2d(int n_x, int n_y)
{
    std::vector<int> neighbors(n_x*n_y*4); // 4 Neighbors per site
    for (int y = 0; y < n_y; ++y)
    {
        for (int x = 0; x < n_x; ++x)
        {
            neighbors[p2i(x, y, n_x, n_y) + 0] = p2i((x-1)%n_x, y, n_x, n_y); // left  neighbor
            neighbors[p2i(x, y, n_x, n_y) + 1] = p2i(x, (y+1)%n_y, n_x, n_y); // upper neighbor
            neighbors[p2i(x, y, n_x, n_y) + 2] = p2i((x+1)%n_x, y, n_x, n_y); // right neighbor
            neighbors[p2i(x, y, n_x, n_y) + 3] = p2i(x, (y-1)%n_y, n_x, n_y); // down  neighbor
        }
    }
    
    return neighbors;
}

template<typename T>
Spingrid<T>::Spingrid(int dim, int n)
 {

    size = std::vector<int> {n, n};
    vol = n*n;
    lattice = std::vector<T>(n*n);

    neighbors = get_neighbors_2d(n, n);
 }

template<typename T>
Spingrid<T>::Spingrid(int dim, int n_x, int n_y)
 {

    size = std::vector<int> {n_x, n_y};
    vol = n_x * n_y;
    lattice = std::vector<T>(n_x*n_y);
    neighbors = get_neighbors_2d(n_x, n_y);


 }

template<typename T>
std::vector<int> Spingrid<T>::get_size()
{
    return size;
}


template<typename T>
void Spingrid<T>::init_cold(T value)
{
    for (int i = 0; i < lattice.size(); ++i)
    {
        lattice[i] = value;
    }
}

template<>
void Spingrid<int>::init_hot(gsl_rng *rng, double p)
{
    double p_temp = 0.0;
    for (int i = 0; i < lattice.size(); ++i)
    {
        p_temp = gsl_rng_uniform(rng);

        if (p_temp <= p) lattice[i] = 1;
        else lattice[i] = -1;
    }
}

// Prints the current lattice configuration
template<typename T>
void Spingrid<T>::print_lattice()
{
    std::cout << "Current lattice configuration: " << std::endl;
    for (int y = 0; y < size[1]; ++y)
    {
        for (int x = 0; x < size[0]; ++x)
        {
            std::cout << lattice[p2i(x, y, size[0], size[1])] << " ";
        }
        std::cout << std::endl;
    }
}

template<>
void Spingrid<int>::spin_flip(int index)
{
    lattice[index] *= (-1);
}

template<typename T>
double Spingrid<T>::get_magnetization()
{
    double mag = 0.0;

    for (auto site:lattice) mag += site;

    return mag/vol;
}

template<typename T>
double Spingrid<T>::get_energy(int J)
{
    std::cout << "This function is not available for this datatype" << std::endl;
    return 0.0;
}

template<>
double Spingrid<int>::get_energy(int J)
{
    double energy = 0.0;

    for (int i = 0; i < lattice.size(); ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            energy += lattice[i] * lattice[neighbors[4*i + j]];
        }
    }

    energy *= J;
    return energy/vol;
}
template class Spingrid<int>;
template class Spingrid<double>;

