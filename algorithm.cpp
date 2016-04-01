#include "algorithm.h"

algorithm::algorithm(){

}
algorithm::algorithm(Flags * flags) {
    try{
         start_evolution(flags);
    }
     catch (errors ix) {
           cout << endl << ix.str << " " << ix.ix << " " << ix.y << endl;
     }
}
void algorithm::start_evolution(Flags * flags) {
    evolution  object_evolution(flags);
    cout << "Start algorithm" << endl;
    object_evolution.start = clock();
    for(int i = 0; i < flags->kolGener; i++){
        object_evolution.create_roulette(flags, i);
        object_evolution.crossover();
        object_evolution.best_fitness(flags, i);
    }
    cout << " time " << object_evolution.end - object_evolution.start;
    QMessageBox msgBox;
    msgBox.setText("End of calculations");
    msgBox.exec();
}
algorithm::~algorithm(){

}
