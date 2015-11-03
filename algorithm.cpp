#include "algorithm.h"

algorithm::algorithm(){

}

algorithm::algorithm(int kolGen, int kolOsob, int number_generation, int p_mut_down, int p_mut_up,  bool flag, double koeff, double stop){

    this->number_generation = number_generation;

    try{

         start_evolution(kolGen, kolOsob, p_mut_down, p_mut_up, flag, koeff, stop);
    }
     catch (errors ix) {

           cout << "ERROR\n" << ix.str << " " << ix.ix << endl;

     }

}

void algorithm::start_evolution(int kolGen, int kolOsob, int p_mut_down, int p_mut_up, bool flag, double koeff, double stop){
    evolution  object_evolution(p_mut_down, p_mut_up, kolGen, kolOsob, koeff, stop); // The percentage of mutations
    double start = clock();
    for(int i = 0; i < number_generation; i++){
        object_evolution.create_roulette(flag);
        object_evolution.krossover();
        object_evolution.best_fitness(i);
//        if((i + 1) % 10 ==0)
//            object_evolution.genocid();

    }
    double  end = clock();
    cout << " time " << end - start;

    QMessageBox msgBox;
    msgBox.setText("End of calculations");
    msgBox.exec();


}

algorithm::~algorithm(){

}
