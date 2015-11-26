#include "algorithm.h"
algorithm::algorithm(){

}
algorithm::algorithm(int kolGen, int kolOsob, int number_generation,
                     int p_mut_down, int p_mut_up,  bool flag,
                     double koeff, double stop,
                     int p_cross_dig_down,
                     int p_cross_flat_down, int p_cross_simple_down,
                     int p_cross_dig_up, int p_cross_flat_up,
                     int p_cross_simple_up, double epsi) {

    this->number_generation = number_generation;
    try{
         start_evolution(kolGen, kolOsob, p_mut_down, p_mut_up,
                         flag, koeff, stop, p_cross_dig_down,
                         p_cross_flat_down, p_cross_simple_down,
                          p_cross_dig_up, p_cross_flat_up,
                         p_cross_simple_up, epsi);
    }
     catch (errors ix) {
           cout << "ERROR\n" << ix.str << " " << ix.ix << endl;
     }
}
void algorithm::start_evolution(int kolGen, int kolOsob, int p_mut_down,
                                int p_mut_up, bool flag,
                                double koeff, double stop,
                                int p_cross_dig_down,
                                int p_cross_flat_down, int p_cross_simple_down,
                                int p_cross_dig_up, int p_cross_flat_up,
                                int p_cross_simple_up, double epsi) {

    evolution  object_evolution(p_mut_down, p_mut_up,
                                kolGen, kolOsob, koeff, stop,
                                p_cross_dig_down, p_cross_flat_down,
                                p_cross_simple_down,
                                p_cross_dig_up, p_cross_flat_up,
                                p_cross_simple_up, epsi);
    double start = clock();
    for(int i = 0; i < number_generation; i++){
        object_evolution.create_roulette(flag);
        object_evolution.crossover();
        object_evolution.best_fitness(i);
    }
    double  end = clock();
    cout << " time " << end - start;
    QMessageBox msgBox;
    msgBox.setText("End of calculations");
    msgBox.exec();
}
algorithm::~algorithm(){

}
