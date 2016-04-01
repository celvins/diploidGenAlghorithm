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
#include "flags.h"
#include <QMessageBox>
class algorithm{
public:
    class errors{
    public:
        char * str;
        double ix;
        int y;
        errors(char er[100], const double x) {str = er; ix = x;}
        errors(char er[100], const double x, const int generate) {str = er; ix = x; y = generate;}
        errors(const double x, const int y){ix = x; this->y = y;}
    };
    algorithm();
    algorithm(Flags *);
    void start_evolution(Flags *);
    ~algorithm();
};

#endif // ALGORITHM_H
