#include "polinomial.h"
#include <math.h>

double Polinomial::polinomy(double x)
{
    return _polinomy(x);
}

double Polinomial::_polinomy(double x)
{
    double y = 0.0;

    if (c.empty())
        return 0.0;

    for (unsigned int i = 0; i < c.size(); i++)
    {
        y += c[i] * pow(x, i);
    }

    return y;
}

void Polinomial::setCoeficientes(std::vector<double> _c)
{
    c = _c;
}
