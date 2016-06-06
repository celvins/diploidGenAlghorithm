#include "evolution.h"

evolution::evolution(){}
evolution::evolution(Flags *flags){
    this->flags = flags;
    object_population = new population(flags->kolOsob, flags->kolGenov);
    object_population->generating_first_popualtion();
    this->minimum = 2000;
}
void evolution::create_roulette(Flags * flags, int generate){
    sum_fitness = 0;
    fitness.clear();
    for(int i = 0; i < flags->kolOsob; i++){
        if(flags->population_file){
            ofstream save_population("population.txt", ios::app);
            if(i == 0) save_population << "NEW generation " << generate << endl;
            for(int j = 0; j < flags->kolGenov; j++) save_population <<  object_population->get_osob(i, j) << " ";
            save_population << endl;
            if(i == flags->kolOsob - 1) save_population << endl << endl;
            save_population.close();
        }
        fitness.push_back(fun.fun(object_population->get_osob(i)));
//        cout << fitness[i] << endl;
        sum_fitness += fabs(fitness[i]);
        if (fitness[i] < flags->stop){
            ofstream file_result("result.txt");
            file_result << "Best fitness in " << generate << " generation " << fitness[i] << endl;
            for(int j = 0; j < flags->kolGenov; j++)
                file_result << object_population->get_osob(i, j) << " ";
            file_result.close();
            end = clock();
            cout << endl << "Time " << end - start;
            QMessageBox msg;
            msg.setText("End calculations");
            msg.exec();
            throw algorithm::errors((char *)"End calculations ", fitness[i], generate);
        }
        if(isnan(fitness[i]))
            throw algorithm::errors((char *)"fitness ", fitness[i]);
    }
    for(int i = 0; i < flags->kolOsob; ++i) object_population->set_hp((fitness[i] / sum_fitness)*100, i);
}
void evolution::crossover(){
    for(int g = 0; g < flags->kolOsob; g++){
        int dad, mom;
        dad = qrand() % flags->kolOsob;
        mom = qrand() % flags->kolOsob;
        QVector<QVector<double> > parents, child;
        for(int i = 0; i < 4; ++i){
            QVector<double> a;
            for(int b = 0; b < flags->kolGenov; b++){
                if(i < 2){
                    if((b + 1) % 2 != 0)
                        a.push_back(object_population->get_osob(dad, b, true));
                    else
                        a.push_back(object_population->get_osob(dad, b, false));
                }
                else{
                    if((b + 1) % 2 != 0)
                        a.push_back(object_population->get_osob(mom, b, true));
                    else
                        a.push_back(object_population->get_osob(mom, b, false));
                }
            }
            parents.push_back(a);
        }
        int crossover_variant = 0;
        int p_crossover = qrand() % 100;
        if (p_crossover >= flags->p_cross_flat_down && p_crossover <= flags->p_cross_flat_up)
            crossover_variant = 0;
        if (p_crossover >= flags->p_cross_dig_down && p_crossover <= flags->p_cross_dig_up)
            crossover_variant = 1;
        if (p_crossover >= flags->p_cross_simple_down && p_crossover <= flags->p_cross_simple_up)
            crossover_variant = 2;
        switch (crossover_variant){
        case 0:
            //division genes in half
            for(int k = 0 ; k < 4; k++){
                QVector<double> a;
                if(k < 3){
                    for(int b = 0; b < flags->kolGenov; b++){
                        if (b <= flags->kolGenov / 2) a.push_back(parents[k + 1][b]);
                        else a.push_back(parents[k][b]);
                    }
                }
                if(k == 3){
                    a.clear();
                    for(int b = 0; b < flags->kolGenov; ++b){
                        if (b <= flags->kolGenov / 2) a.push_back(parents[0][b]);
                        else a.push_back(parents[2][b]);
                    }
                }
                child.push_back(a);
            }
            break;
        case 1:
            //Discrete crossover
            for(int i = 0; i < 4; i+=2){
                QVector<double> a, c;
                for(int b = 0; b < flags->kolGenov; b++){
                    int rnd = qrand() % 2;
                    if(rnd == 0){
                        a.push_back(parents[i][b]);
                        c.push_back(parents[i + 1][b]);
                    }
                    else{
                        a.push_back(parents[i + 1][b]);
                        c.push_back(parents[i][b]);
                    }
                }
                child.push_back(a);
                child.push_back(c);
            }
            break;
        case 2:
            //Simple сrossover
            int i = qrand() % (flags->kolGenov);
            for(int k = 0 ; k < 4; ++k){
                QVector<double> a;
                for(int b = 0; b < flags->kolGenov; b++){
                    if(b < i) a.push_back(parents[k][b]);
                    else{
                        if((k + 1) % 2 == 0) a.push_back(parents[k][b]);
                        else a.push_back(parents[k + 1][b]);
                    }
                }
                child.push_back(a);
            }
            break;
//        case 3:
//            //Crossover best vith best
//            for(int k = 0 ; k < 4; ++k){
//                QVector<double> a;
//                for(int b = 0; b < N; b++){
//                    if(b % 2 == 0){
//                        child[0][b] = parents[0][b];
//                        child[1][b] = parents[1][b];
//                    }
//                    else {
//                        child[1][b] = parents[0][b];
//                        child[0][b] = parents[1][b];
//                    }
//                }
//            }
//            break;
        }
        //best krossover
      double fitness_child[4];
       int i_worst, i_best1, i_best2;
       if(fitness[dad] < fitness[mom])
           i_worst = mom;
       else
           i_worst = dad;
        for(int i = 0; i < 4; i++){
            mutation(child[i]);
            fitness_child[i] = fun.fun(child[i]);
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
        object_population->decoding_genes(i_worst);
//        object_population->limited_border(i_worst);
    }
}
void evolution::mutation(QVector<double> &popul){
    int p_mutation = qrand() % 100; //The probability of an individual gene mutation
    if (p_mutation <= flags->p_mut_up){
        for (int b = 0; b < flags->kolGenov; b++){
           int p_mut = qrand() % 100;
           if (p_mut > flags->p_mut_up) continue;
           double mut = qrand() * 0.3 / (double)RAND_MAX;
           double a = (popul[b] - popul[b] * mut);
           double c = (popul[b] + popul[b] * mut);
           if (a < c) popul[b] = a + qrand() * (c - a) / (double)RAND_MAX;
           else popul[b] = c + qrand() * (a - c) / (double)RAND_MAX;
         }
    }
}
void evolution::best_fitness(Flags * flags, int j){
    int i_min;
    if(flags->best_file){
        double min = fitness[0];
        i_min = 0;
        for(int i = 1; i < flags->kolOsob; i++){
           if(fitness[i] < min){
               min = fitness[i];
               i_min = i;
               end = clock();
           }
        }
        ofstream file_best_fitness("best_fitness.txt", ios::app);
        file_best_fitness << "Best fitness in " << j << " generation " << min << endl;
        for(int i = 0; i < flags->kolGenov; i++)
            file_best_fitness << object_population->get_osob(i_min, i) << " ";
        file_best_fitness << endl;
        file_best_fitness.close();
    }
    if(flags->best_all_file && flags->best_file){
        if (fitness[i_min] < minimum){
            minimum = fitness[i_min];
            ofstream file_best_all_generations("best_all.txt");
            file_best_all_generations<< "Population № " << j + 1 << "\nBest of all fitness " << minimum << "\nBest individual\n";
            for(int i = 0; i < flags->kolGenov; i++)
                file_best_all_generations << object_population->get_osob(i_min, i) << " ";
            file_best_all_generations.close();
            cout << minimum << endl;
        }
    }
    if (((j + 1) % 150) == 0) genocid(true);
    if (((j + 1) % 350) == 0) genocid(false);
}
void evolution::genocid(bool flag){
    if(flag){
        QVector<QVector<int> > a;
        for(int i = 0; i < flags->kolOsob; ++i){
            a.push_back(QVector<int>());
            a[i].push_back(i); a[i].push_back(object_population->get_hp(i));
        }
        for(int i = 0; i < flags->kolOsob - 1; ++i){
            bool swap = false;
            for(int j = 0; j < flags->kolOsob - i - 1; ++j){
                if(a[j][1] > a[j + 1][1]){
                    QVector<int> b;
                    b.swap(a[j]);
                    a[j].swap(a[j + 1]);
                    a[j + 1].swap(b);
                    swap = true;
                }
            }
            if(!swap)
                break;
        }
        for(int i = flags->kolGenov / 2; i < flags->kolOsob; ++i){
            for(int j = 0; j < flags->kolOsob; ++j){
                if(a[i][0] == j)
                    object_population->generating_new_population(j);
            }
        }
    }
    else{
        for(int i = 0; i < flags->kolOsob; ++i){
            int j = qrand() % flags->kolOsob;
            object_population->generating_new_population(j);
        }

    }
}
evolution::~evolution(){
    delete object_population;
}
