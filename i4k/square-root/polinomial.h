#ifndef POLINOMIAL_H
#define POLINOMIAL_H

#include <vector>

class Polinomial
{
public:
    void setCoeficientes(std::vector<double> _c);
    double polinomy(double x);
    double _polinomy(double x);

protected:
    std::vector<double> c;
};

#endif // POLINOMIAL_H
