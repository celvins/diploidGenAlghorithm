/**
 * \author Vardanyan Andranik Eduardovich
 * \date 15.10.2015
 * \brief Запускает геннетический алгоритм.
 * \param [in] number_generation число поколений. Задается пользователем.
 *
 *
*/
#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "population.h"
#include "evolution.h"
#include <QMessageBox>

class algorithm{
private:
    int number_generation;
public:
    class errors{
    public:
        char * str;
        double ix;
        int y;
        errors(char er[100], const double x) {str = er; ix = x;}
        errors(const double x, const int y){ix = x; this->y = y;}
    };
    algorithm();
    algorithm(int, int, int, int, int, bool, double, double, int, int, int, int, int, int, double);
    void start_evolution(int, int, int, int, bool, double, double, int, int, int, int, int, int, double);
    ~algorithm();
};

#endif // ALGORITHM_H
