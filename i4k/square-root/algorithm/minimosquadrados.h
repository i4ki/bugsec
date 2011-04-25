#ifndef MINIMOSQUADRADOS_H
#define MINIMOSQUADRADOS_H

#include <vector>
#include "curve.h"

class MinimosQuadrados
{
public:
    MinimosQuadrados();
	~MinimosQuadrados();
    void setExperimentalData(Curve c);
    void setExperimentalData(const std::vector<Point> p);
    void setGrauPolin(int g) { graupolin = g; }
    std::vector<double> calcular();
    std::vector<double> somatorioXmulY(const std::vector<double> matrix_x, const std::vector<double> matrix_y);
    std::vector<double> somatorioPotenciaX(const std::vector<double> matrix_x);
    Curve getCurve() { return curve; }
    double getCoefCorrelacao() const { return coef_correlacao; }

    /* Vulgo LUBKSB */
    void methodLU_Backsubstitution(std::vector<std::vector<double> > matrix_a, double *B, int *INDX, int graupolin);

    /* Vulgo LUDCMP */
	std::vector<std::vector<double> > methodLU_Decomposition(std::vector<std::vector<double> > matrix_a, int n, int *INDX);
protected:
    /* Grau do polinomio */
    int graupolin;
	
    /* Coeficiente de correlação */
    double coef_correlacao;

    /* Numero de pontos experimentais */
    int numeropontos;

    /* Curva */
    Curve curve;

    /* Cálculo do somatório de y*x com cada x elevado ao expoente i=0,1...*/
    std::vector<double> vetor_xy;

    std::vector<double> soma_x;
};

#endif // MINIMOSQUADRADOS_H
