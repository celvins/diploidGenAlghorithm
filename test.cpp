#include "test.h"
#include "population.h"
#include "iostream"

double fun(double * x, int kol){
    double result = 0;
    for(int j = 0; j < kol - 1; j++){
        result += (100 * (pow(x[j + 1] - pow(x[j], 2), 2)) + pow(1 - x[j], 2)); //Розенброк
    }
//    for(int i = 0; i < kol; i++){
//        result += (x[i] * sin(pow(fabs(x[i]), 0.5)));
//    }
//    result = -result * 0.16667;
//    std::cout << result <<std::endl;
    return result;
}
