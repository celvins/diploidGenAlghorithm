#include "evolution.h"
#include <omp.h>
evolution::evolution(){

    roulette = new double[object_population->get_kol_osob()];
    fitness = new double[object_population->get_kol_osob()];
}


evolution::evolution(int p_mutation_down, int p_mutation_up, int kolGen, int kolOsob, double koeff, double stop){

    object_population = new population(kolOsob, kolGen);
    this->koef = koeff;
    this->stop_min = stop;
    object_population->generating_first_popualtion();
    this->P_MUTATION_DOWN = p_mutation_down;
    this->P_MUTATION_UP = p_mutation_up;

    roulette = new double[object_population->get_kol_osob()];
    fitness = new double[object_population->get_kol_osob()];
}

void evolution::create_roulette(bool save_population_in_file){

    if(save_population_in_file){

        ofstream save_population("population.txt", ios::app);
        save_population << "NEW generation" << endl;
        for(int i = 0; i < object_population->get_kol_osob(); i++){
            for(int j = 0; j < object_population->get_kol_genov(); j++)
                save_population << object_population->get_osob(i, j) << " ";
            save_population << endl;
        }
        save_population << endl << endl;
        save_population.close();
    }

    roulette_sum = 0;

    for(int i = 0; i < object_population->get_kol_osob(); i++){

        double * ptr = object_population->get_osob(i);
        fitness[i] = fun(ptr, object_population->get_kol_genov());
        if(isnan(fitness[i]))
            throw algorithm::errors((char *)"fitness ", fitness[i]);
        roulette_sum += 1 / (fitness[i]+koef);
    }


        roulette[0] = 1 / (fitness[0]+koef);

        for(int i = 1; i < object_population->get_kol_osob(); i++)
            roulette[i] = roulette[i - 1] + 1 / (fitness[i]+koef);



}

int evolution::choice_parent(double x){
    for(int i = 0; i < object_population->get_kol_osob(); i++){
        if (x < roulette[i])
           return i;

    }
//    cout << "error_choice_parent" << endl << endl;
    return 0;
}

void evolution::krossover(){


    for(int g = 0; g < object_population->get_kol_osob(); g ++){

        double x_dad, x_mom;
        x_dad = roulette_sum + rand() * (roulette[0]-roulette_sum ) /(double)RAND_MAX;
        x_mom = roulette_sum + rand() * (roulette[0]-roulette_sum ) /(double)RAND_MAX;


        int dad = choice_parent(x_dad), mom = choice_parent(x_mom);

        double parents[4][object_population->get_kol_genov()], child[4][object_population->get_kol_genov()];

        for(int b = 0; b < object_population->get_kol_genov(); b++){

            parents[0][b] = object_population->get_osob(dad, b, true);
            parents[1][b] = object_population->get_osob(dad, b, false);
            parents[2][b] = object_population->get_osob(mom, b, true);
            parents[3][b] = object_population->get_osob(mom, b, false);

        }

        int krossover_variant = 1;
        int p_krossover = rand() % 100;
        if (p_krossover >= 0 && p_krossover <= 1)
            krossover_variant = 0;
        if (p_krossover >= 2 && p_krossover <= 90)
            krossover_variant = 1;
        if (p_krossover >= 91 && p_krossover <= 100)
            krossover_variant = 2;

        switch (krossover_variant){
        case 0:
            //Flat crossover

            for(int i = 0; i < 4; i+=2){
                for(int b = 0; b < object_population->get_kol_genov(); b++){

                    if(parents[i][b] == parents[i + 1][b]){
                        child[i][b] = parents[i][b];
                        child[i + 1][b] = parents[i][b];
                        continue;
                    }

                    if(parents[i][b] < parents[i + 1][b]){
                        child[i][b] = (parents[i + 1][b] + rand() * (parents[i][b] - parents[i + 1][b]) / (double) RAND_MAX);
                        child[i + 1][b] = (parents[i + 1][b] + rand() * (parents[i][b] - parents[i + 1][b]) / (double) RAND_MAX);
                        continue;
                    }
                    else{
                        child[i][b] = (parents[i][b] + rand() * (parents[i + 1][b] - parents[i][b]) / (double) RAND_MAX);
                        child[i + 1][b] = (parents[i][b] + rand() * (parents[i + 1][b] - parents[i][b]) / (double) RAND_MAX);
                        continue;
                    }
                }
            }
            break;
        case 1:
            //
            for(int i = 0; i < 4; i+=2){
                for(int b = 0; b < object_population->get_kol_genov(); b++){

                    int rnd = rand() % 2;
                    if(rnd == 0){
                        child[i][b] = parents[i][b];
                        child[i + 1][b] = parents[i + 1][b];
                    }
                    else{
                        child[i][b] = parents[i + 1][b];
                        child[i + 1][b] = parents[i][b];
                    }
                }
            }
            break;
        case 2:

            int i = rand() % (object_population->get_kol_genov());
            for(int b = 0; b < object_population->get_kol_genov(); b++){

                if(b < i){

                    child[0][b] = parents[0][b];
                    child[1][b] = parents[1][b];
                    child[2][b] = parents[2][b];
                    child[3][b] = parents[3][b];
                }
                else{

                    child[1][b] = parents[0][b];
                    child[0][b] = parents[1][b];
                    child[3][b] = parents[2][b];
                    child[2][b] = parents[3][b];
                }
            }
            break;
        }

        //best krossover
      double fitness_child[4];
       int i_worst = 0, i_best1, i_best2;

        if(fitness[dad] < fitness[mom])

            i_worst = mom;
        else

            i_worst = dad;

        for(int i = 0; i < 4; i++){

            mutation(child[i]);
            fitness_child[i] = fun(child[i], object_population->get_kol_genov());
        }

        if(fitness_child[0] < fitness_child[2])

            i_best1 = 0;
        else

            i_best1 = 2;

        if(fitness_child[1] < fitness_child[3])

            i_best2 = 1;
        else

            i_best2 = 3;

        if(fitness_child[i_best1] < fitness_child[i_best2]){

            object_population->set_osob(child[i_best1], i_worst, true);
            object_population->set_osob(child[i_best2], i_worst, false);
        }
        else{

            object_population->set_osob(child[i_best2], i_worst, true);
            object_population->set_osob(child[i_best1], i_worst, false);
        }

    }

    object_population->decoding_genes();
}

void evolution::mutation(double * popul){

        for(int b = 0; b < object_population->get_kol_genov(); b++){

            int p_mutation = rand() % 100; //The probability of an individual gene mutation
            if((p_mutation >= P_MUTATION_DOWN) && (p_mutation <= P_MUTATION_UP)){

                double a = (popul[b] - popul[b] * 0.25);
                double c = (popul[b] + popul[b] * 0.25);
                if(a < c){

                    popul[b] = a + rand() * (c - a) / (double)RAND_MAX;
                }
                else{

                    popul[b] = c + rand() * (a - c) / (double)RAND_MAX;
                }
            }
        }
}

evolution::~evolution(){

    delete object_population;
    delete []roulette;
    delete []fitness;

}

void evolution::best_fitness(int j){

    ofstream file_best_fitness("best_fitness.txt", ios::app);
    double min = fitness[0];
    int i_min = 0;
    for(int i = 1; i < object_population->get_kol_osob(); i++){

           if(fitness[i] < min){

               min = fitness[i];
               i_min = i;
           }
    }
    if(j == 0)
        minimum = min;

    file_best_fitness << "Best fitness in " << j << " generation " << min << endl;
    for(int i = 0; i < object_population->get_kol_genov(); i++)
        file_best_fitness << object_population->get_osob(i_min, i) << " ";

    file_best_fitness << endl;
    file_best_fitness.close();

    if(fitness[i_min] < minimum){

        minimum = fitness[i_min];
        ofstream file_best_all_generations("best_all.txt");
        file_best_all_generations<< "Population № " << j + 1 << "\nBest of all fitness " << minimum << "\nBest individual\n";
        for(int i = 0; i < object_population->get_kol_genov(); i++)
            file_best_all_generations << object_population->get_osob(i_min, i) << " ";
        file_best_all_generations.close();
    }


    if( fitness[i_min] < stop_min){

        QMessageBox msg;
        msg.setText("End calculations");
        msg.exec();
        throw algorithm::errors((char *)"End calculations ", fitness[i_min]);
    }

    if(((j + 1) % (object_population->get_kol_osob()))  == 0)
        genocid();

}
void evolution::genocid(){
    double e = 0.1;
    int i = 0;
    while(i < object_population->get_kol_osob() - 1){

            for(int k = i; k < object_population->get_kol_osob(); k++){
                double sum = 0;
                for(int j = 0; j < object_population->get_kol_genov(); j++){
                    double a = object_population->get_osob(i, j);
                    double b = object_population->get_osob(k, j);
                    sum += pow(a - b, 2);
                }
                if(sum <= e){
                    object_population->generating_new_population(k);
                    object_population->decoding_genes(k);
                }

            }
        i++;
    }

}

