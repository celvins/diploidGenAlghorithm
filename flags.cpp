#include "flags.h"

Flags::Flags()
{

}

Flags::Flags(int kolGenov, int kolOsob, int kolGener, int p_mut_down, int p_mut_up, int p_cross_dig_down, int p_cross_flat_down, int p_cross_simple_down,
             int p_cross_dig_up, int p_cross_flat_up, int p_cross_simple_up, double koef, double stop, double epsi, bool best_file, bool best_all_file, bool population_file)
{
    this->best_file = best_file;
    this->best_all_file = best_all_file;
    this->population_file = population_file;
    this->epsi = epsi;
    this->koef = koef;
    this->kolGener = kolGener;
    this->kolGenov = kolGenov;
    this->kolOsob = kolOsob;
    this->p_cross_dig_down = p_cross_dig_down;
    this->p_cross_dig_up = p_cross_dig_up;
    this->p_cross_flat_down = p_cross_flat_down;
    this->p_cross_flat_up = p_cross_flat_up;
    this->p_cross_simple_down = p_cross_simple_down;
    this->p_cross_simple_up = p_cross_simple_up;
    this->p_mut_down = p_mut_down;
    this->p_mut_up = p_mut_up;
    this->stop = stop;
}

