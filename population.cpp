#include "population.h"
#include "algorithm.h"

Individual::Individual(){}
void Individual::set_hp(double hp){this->hp = hp;}
double Individual::get_hp(){return this->hp;}
Individual::Individual(int kol_genov, QVector<QVector<double> > dom){
//    qsrand(random_device().operator ()());
    this->kol_genov = kol_genov;
    this->domination = dom;
}
////////////////////////////////////////////////
void Individual::set_genotype(QVector<QVector<double> > border){///////////////////////////////!!!!!!!!!!!!!!!!!!!!!
    genotype.clear();
    for(int j = 0; j < kol_genov; j++){
        genotype.push_back(border[j][0] * pow(10,border[j][1]) + qrand() * (border[j][2] * pow(10,border[j][3]) - border[j][0] * pow(10,border[j][1])) /(double)RAND_MAX);
    }
}
/////////////////////////////////////////////////////
void Individual::decoding_genes(bool first){
    double length1 = 0, length2 = 0;
    genotype.clear();
    for(int j = 0; j < kol_genov; j++){
        bool flag1 = false, flag2 = false;
        if(best_parent[j] >= domination[j][0] * pow(10, domination[j][1]) && best_parent[j] <= domination[j][2] * pow(10, domination[j][3]))
            flag1 = true;
        if(this->bed_parent[j] >= domination[j][0] * pow(10, domination[j][1]) && bed_parent[j] <= domination[j][2] * pow(10, domination[j][3]))
            flag2 = true;
        if(first){
                if(bed_parent[j] < domination[j][0] * pow(10, domination[j][1]))
                    length1 = domination[j][0] * pow(10, domination[j][1]) - bed_parent[j];
                else
                    length1 = bed_parent[j] - domination[j][2] * pow(10, domination[j][3]);
                if(best_parent[j] < domination[j][0] * pow(10, domination[j][1]))
                    length2 = domination[j][0] * pow(10, domination[j][1]) - best_parent[j];
                else
                    length2 = best_parent[j] - domination[j][2] * pow(10, domination[j][3]);
                if(fabs(length1) < fabs(length2)){
                    genotype.push_back(bed_parent[j]);
                    continue;
                }
                else{
                    genotype.push_back(best_parent[j]);
                    continue;
                }
        }
        if(flag1){
           genotype.push_back(best_parent[j]);
            continue;
        }
        if(flag2){
           genotype.push_back(bed_parent[j]);
            continue;
        }
        if(!flag1 && !flag2){
            genotype.push_back(best_parent[j]);
        }
    }
}
void Individual::set_individuals(QVector<QVector<double> > border){
    for(int j = 0; j < kol_genov; j++){
        best_parent.push_back(border[j][0] * pow(10,border[j][1]) + qrand() * (border[j][2] * pow(10,border[j][3]) - border[j][0] * pow(10,border[j][1])) /(double)RAND_MAX);
        bed_parent.push_back(border[j][0] * pow(10,border[j][1]) + qrand() * (border[j][2] * pow(10,border[j][3]) - border[j][0] * pow(10,border[j][1])) /(double)RAND_MAX);
    }
}
void Individual::set_zigota(QVector<double> zigota, bool flag){
    if(flag) best_parent = zigota;
    else bed_parent = zigota;
}
QVector<double> Individual::get_individual_genotype(){
    return genotype;
}
double Individual::get_individual_gen(int j){
    return genotype[j];
}
double Individual::get_individual_gen(int j, bool flag){
    if(flag)
        return best_parent[j];
    else
        return bed_parent[j];
}
Individual::~Individual(){

}

population::population(){}
population::population(int kol_osob, int kol_genov){
    this->kol_osob = kol_osob;
    this->kol_genov = kol_genov;
    ifstream border_file("border.txt", ios::in); //file for reading borders genes
    if (border_file.fail())
       throw algorithm::errors((char *)"read of border.txt", -1);
    for(int i = 0; i < kol_genov; i++){
        QVector<double> a;
        for(int j = 0; j < 4; j++){
            double b;
            border_file >> b;
            a.push_back(b);
        }
        border.push_back(a);
    }
    border_file.close();
    ifstream border_domination("border_domination.txt", ios::in); //file for reading borders domination
    if (border_domination.fail())
       throw algorithm::errors((char *)"read of border_domination.txt", -1);
     QVector<QVector<double> > domination;
    for(int i = 0; i < kol_genov; i++){
        QVector<double> a;
        for(int j = 0; j < 4; j++){
            double b;
            border_domination >> b;
            a.push_back(b);
        }
        domination.push_back(a);
    }
    border_domination.close();
    for(int i = 0; i < kol_osob; ++i){
        Individual * objIndividual = new Individual(kol_genov, domination); // bez *!!!!!
        individual.push_back(objIndividual);
    }
}
void population::set_hp(double hp, int i){
    individual[i]->set_hp(hp);
}
double population::get_hp(int i){
    return individual[i]->get_hp();
}

void population::generating_first_popualtion(){
    for(int i = 0; i < kol_osob; i++){
         individual[i]->set_individuals(border);
         individual[i]->decoding_genes(true);
    }
}
///////////////////////////////////////
void population::generating_new_population(int k){
    individual[k]->set_genotype(border);///////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
//////////////////////////////////////////
void population::decoding_genes(int i){
    individual[i]->decoding_genes(false);
}
QVector<double> population::get_osob(int i){
    return individual[i]->get_individual_genotype();
}
double  population::get_osob(int i, int j){
    return individual[i]->get_individual_gen(j);
}
double population::get_osob(int i, int j, bool flag){
    return individual[i]->get_individual_gen(j, flag);
}
int population::get_kol_osob(){
    return kol_osob;
}
int population::get_kol_genov(){
    return kol_genov;
}
void population::set_osob(QVector<double> individual, int i, bool flag){
    this->individual[i]->set_zigota(individual, flag);
}
void population::limited_border(int i){
    bool flagi = false;
    for(int j = 0; j < kol_genov; ++j){
        if(get_osob(i, j) < border[j][0] * pow(10,border[j][1]) || get_osob(i, j) > border[j][2] * pow(10,border[j][3]))
            flagi = true;
    }
    if(flagi){
        individual[i]->set_individuals(border);
        individual[i]->decoding_genes(true);
    }
}
population::~population(){

}

