#ifndef FUN_H
#define FUN_H

#include "fun_global.h"
#include <QVector>
#include "math.h"

class FUNSHARED_EXPORT Fun
{

public:
    Fun();
    long double fun(QVector<double>);
};

#endif // FUN_H
