#ifndef POPULATION_H
#define POPULATION_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;
/**
    * \brief Класс Individual представляет собой три склееных вектора best_parent, bed_parent, genotype;
    * \param [in] best_parent зигота лучшей особи
    * \param [in] bed_parent зигота худшей особи
    * \param [in] genotype получается путем декодирования по следующим правилам
    *    (Правила решения конфликта доминантности):
    *    1) Если генн соответствует диапозону доминантности то выбирается доминантный ген;
    *    2) Если оба гена доминантны то предпочтение отдается более приспособленной особи;
    *    3) Если оба гена рецесивны то предпочтение отдается более приспособленной особи;

*/
class Individual{
private:
    int kol_genov;
    double * best_parent;
    double * bed_parent;
    double * genotype;
    double ** domination;
public:
    Individual();
    Individual(int, double **); //В качестве параметра получает кол-во неизвестных коэф-ов
    void decoding_genes(bool); //Декодирование геннов. В качестве параметра получает диапозон доминантности
    void set_individuals(double **); //Генерирует начальную популяция. Аргумент диапозон возможных значений генна
    void set_zigota(double *, bool); //Устанавливает значения best_parent и bed_parent. В качестве аргумент - одномерный массив и flag                                                                                     //true - best; false - bed
    double * get_individual_genotype(); //Возвращает одномерный массив genotype
    double get_individual_gen(int);//Возвращает значение массива genotype. В качестве аргумента принимает индекс столбца.
    double get_individual_gen(int, bool); //Возвращает значение best_parent или bed_parent в зависимости от флага
    ~Individual();
};
class population{
private:
    Individual * objIndividual;
    vector<Individual*> individual;
    int kol_osob;
    int kol_genov;
    double ** border;
public:
    population();
    population(int , int);
    void limited_border();
    void generating_new_population(int);
    void generating_first_popualtion();
    void decoding_genes();
    void decoding_genes(int);
    void set_osob(double *, int, bool);
    double *get_osob(int);
    double get_osob(int, int);
    double get_osob(int, int, bool);
    int get_kol_osob();
    int get_kol_genov();
    int get_border_dominantion_up();
    int get_border_dominantion_down();
    ~population();
};

#endif // POPULATION_H
