#ifndef FLAGS_H
#define FLAGS_H


class Flags{
public:
    bool best_file, best_all_file, population_file;
    double koef, epsi, stop;
    int kolGenov, kolOsob, kolGener, p_mut_down, p_mut_up,
       p_cross_dig_down, p_cross_flat_down, p_cross_simple_down,
       p_cross_dig_up, p_cross_flat_up, p_cross_simple_up;
public:
    Flags();
    Flags(int, int, int, int, int, int, int, int,
          int, int, int, double, double, double, bool, bool, bool);
};

#endif // FLAGS_H
