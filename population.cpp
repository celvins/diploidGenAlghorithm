#include "population.h"
#include "algorithm.h"

Individual::Individual(){

}
Individual::Individual(int kol_genov, double ** dom){
    qsrand(time(NULL));
    this->kol_genov = kol_genov;
    this->domination = dom;
    best_parent = new double[kol_genov];
    bed_parent = new double[kol_genov];
    genotype = new double[kol_genov];
}
void Individual::decoding_genes(bool first){
    double length1 = 0, length2 = 0;
    for(int j = 0; j < kol_genov; j++){
        bool flag1 = false, flag2 = false;
        if(best_parent[j] >= domination[j][0] && best_parent[j] <= domination[j][1])
            flag1 = true;
        if(this->bed_parent[j] >= domination[j][0] && bed_parent[j] <= domination[j][1])
            flag2 = true;
        if(first){
            if((flag1 && flag2) || (!flag1 && !flag2) || (flag1 && !flag2) || (!flag1 && flag2)){
                if(bed_parent[j] < domination[j][0])
                    length1 = domination[j][0] - bed_parent[j];
                else
                    length1 = bed_parent[j] - domination[j][1];
                if(best_parent[j] < domination[j][0])
                    length2 = domination[j][0] - best_parent[j];
                else
                    length2 = best_parent[j] - domination[j][1];
                if(fabs(length1) < fabs(length2)){
                    genotype[j] = bed_parent[j];
                    continue;
                }
                else{
                    genotype[j] = best_parent[j];
                    continue;
                }
            }
        }
        if(flag1){
           genotype[j] = best_parent[j];
            continue;
        }
        if(flag2){
           genotype[j] = bed_parent[j];
            continue;
        }
        if(!flag1 && !flag2){
            if(bed_parent[j] < domination[j][0])
                length1 = domination[j][0] - bed_parent[j];
            else
                length1 = bed_parent[j] - domination[j][1];
            if(best_parent[j] < domination[j][0])
                length2 = domination[j][0] - best_parent[j];
            else
                length2 = best_parent[j] - domination[j][1];
            if(fabs(length1) < fabs(length2)){
                genotype[j] = bed_parent[j];
                continue;
            }
            else{
                genotype[j] = best_parent[j];
                continue;
            }
        }
    }
}
void Individual::set_individuals(double ** border){
    for(int j = 0; j < kol_genov; j++){
        best_parent[j] = border[j][0] * pow(10,border[j][1]) + qrand() * (border[j][2] * pow(10,border[j][3]) - border[j][0] * pow(10,border[j][1])) /(double)RAND_MAX;
        bed_parent[j] = border[j][0] * pow(10,border[j][1]) + qrand() * (border[j][2] * pow(10,border[j][3]) - border[j][0] * pow(10,border[j][1])) /(double)RAND_MAX;
    }
}
void Individual::set_zigota(double * zigota, bool flag){
    if(flag)
        for(int i = 0; i < kol_genov; i++)
            best_parent[i] = zigota[i];
    else
        for(int i = 0; i < kol_genov; i++)
            bed_parent[i] = zigota[i];
}
double * Individual::get_individual_genotype(){
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
    delete []bed_parent;
    delete []best_parent;
    delete []genotype;
}
population::population(){

}
population::population(int kol_osob, int kol_genov){
    this->kol_osob = kol_osob;
    this->kol_genov = kol_genov;
    ifstream border_file("border.txt", ios::in); //file for reading borders genes
    if (border_file.fail())
       throw algorithm::errors((char *)"read of border.txt", -1);
    border = new double*[kol_genov];
    for(int i = 0; i < kol_genov; i++)
        border[i] = new double[4];
    for(int i = 0; i < kol_genov; i++)
        for(int j = 0; j < 4; j++)
            border_file >> border[i][j];
    border_file.close();
    ifstream border_domination("border_domination.txt", ios::in); //file for reading borders domination
    if (border_domination.fail())
       throw algorithm::errors((char *)"read of border_domination.txt", -1);
    double ** domination = new double*[kol_genov];
    for(int i = 0; i < kol_genov; i++)
        domination[i] = new double[2];
    for(int i = 0; i < kol_genov; i++)
        for(int j = 0; j < 2; j++)
            border_domination >> domination[i][j];
    border_domination.close();
    for(int i = 0; i < kol_osob; i++){
        objIndividual = new Individual(kol_genov, domination);
        individual.push_back(objIndividual);
    }
    delete []domination;
    for(int i = 0; i < kol_genov; i++){
        delete []domination[i];
    }
}
void population::generating_first_popualtion(){
    for(int i = 0; i < kol_osob; i++){
         individual[i]->set_individuals(border);
         individual[i]->decoding_genes(true);
    }
}
void population::generating_new_population(int k){
    individual[k]->set_individuals(border);
}
void population::decoding_genes(){
    for(int i = 0; i < kol_osob; i++){
        individual[i]->decoding_genes(false);
    }
}
void population::decoding_genes(int i){
    individual[i]->decoding_genes(true);
}
double * population::get_osob(int i){
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
void population::set_osob(double * individual, int i, bool flag){
    this->individual[i]->set_zigota(individual, flag);
}
population::~population(){
    for(int i = 0; i < kol_osob; i++)
        delete individual[i];
    delete objIndividual;
    delete []border;
    for(int i = 0; i < kol_genov; i++){
        delete []border[i];
    }
}
