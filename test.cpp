#include "test.h"

double fun(QVector<double> x){
    return 3 * pow(x[0],2) + x[0] * x[1] + 2 * pow(x[1],2) - x[0] - 4 * x[1];
}
