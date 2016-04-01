/**
 *
 * \author Vardanyan Andranik Eduardovich
 * \date 15.10.2015
 * \brief Клас evolution. Описывает два базовых генетических оператора : Мутация, Кроссовер
 *
 * \param [in] object_population объект класса population.
 * \param [in] roulette массив для хранения приспособленности особи
 * \param [in] fitness массив для хранения значений функции
 * \param [in] roulette_sum
 *  \param [in] P_MUTATION_DOWN нижняя граница вероятности мутации для особи
 *  \param [in] P_MUTATION_UP верхняя граница вероятности мутации для особи
 *  \param [in] koef дополнительный коэффициент. Если программа ищет отрицательный миннимум
 *  \param [in] stop_min примерное значение результата программы. Для преждевременной остановки алгоритма
 *
 *
 *
*/
#ifndef EVOLUTION_H
#define EVOLUTION_H
#include "population.h"
#include "test.h"
#include "algorithm.h"
#include "flags.h"
#include "omp.h"
#include <time.h>
#include <QMessageBox>
#include <random>
#include <ctime>
class evolution{
private:
    population * object_population;
    Flags * flags;
    QVector<double> fitness;
    double sum_fitness, koef, minimum, stop_min, epsi;
    int P_MUTATION_UP, P_MUTATION_DOWN, p_cross_dig_down, p_cross_flat_down, p_cross_simple_down,
        p_cross_dig_up, p_cross_flat_up, p_cross_simple_up;
    bool best, best_all;
public:
    double start, end;
    evolution();
    evolution(Flags * flags);
    void create_roulette(Flags *, int);
    void limited_border(QVector<double>);
    void crossover();
    void mutation(QVector<double> &);
    void genocid(bool);
    void best_fitness(Flags *, int);
    ~evolution();
};
#endif // EVOLUTION_H
