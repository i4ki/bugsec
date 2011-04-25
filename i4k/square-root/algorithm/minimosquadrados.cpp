#include "minimosquadrados.h"
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#define DEBUG_VAR(name, value) cout << name << "=" << value << endl;
#define DEBUG_MSG(msg) cout << msg << endl;

using std::cout;
using std::endl;
using std::vector;

typedef vector<vector<double> > matrix;

MinimosQuadrados::MinimosQuadrados()
    : graupolin(0)
    , numeropontos(0)    
{

}

MinimosQuadrados::~MinimosQuadrados()
{
	
}

void MinimosQuadrados::setExperimentalData(Curve c)
{
    curve = c;
}

void MinimosQuadrados::setExperimentalData(const vector<Point> p)
{
    if (curve.getPoints().size() > 0)
        curve.clear();

    curve.addPointByArray(p);
}

std::vector<double> MinimosQuadrados::somatorioXmulY(const vector<double> matrix_x, const vector<double> matrix_y)
{
    vector<double> mulXY(graupolin+1);

    for (int i = 0; i <= graupolin; i++)
    {
        mulXY[i] = 0.0;

        for (unsigned int j = 0; j < matrix_x.size(); j++)
        {
			mulXY[i] = mulXY[i] + matrix_y[j] * pow(matrix_x[j], i);
        }
    }
        
    return mulXY;
}

vector<double> MinimosQuadrados::somatorioPotenciaX(const vector<double> matrix_x)
{
    vector<double> soma_x(2*graupolin + 1);

    for (int i = 0; i <= 2*graupolin; i++)
    {
        soma_x[i] = 0.0;

        for (unsigned int j = 0; j < matrix_x.size(); j++)
            soma_x[i] = soma_x[i] + pow(matrix_x[j], i);
    }

    return soma_x;
}

matrix MinimosQuadrados::methodLU_Decomposition(matrix matrix_a, int n, int *indx)
{
    int i, j, imax, k;
    double big, dum, sum, temp;
    vector<double> vv(n);
    const double TINY = 1.0e-20;
    double d = 1.0;
	
    for (i = 0; i < n; i++)
    {
        big = 0.0;
        for (j = 0; j < n; j++)
        {
            if ((temp = fabs(matrix_a[i][j])) > big)
                big = temp;
        }
		
        if (big == 0.0)
            throw std::string("Matriz Singular");

        vv[i] = 1.0 / big;		
    }
	
    for (j = 0; j < n; j++)
    {
        for (i = 0; i < j; i++)
        {
            sum = matrix_a[i][j];
		
            for (k = 0; k < i; k++)
                sum -= matrix_a[i][k] * matrix_a[k][j];

            matrix_a[i][j] = sum;
        }

        big = 0.0;

        for (i = j; i < n; i++)
        {
            sum = matrix_a[i][j];
            for (k = 0; k < j; k++)
                sum -= matrix_a[i][k] * matrix_a[k][j];

            matrix_a[i][j] = sum;

            if ((dum = vv[i] * fabs(sum)) >= big)
            {
                big = dum;
                imax = i;
            }
        }

        if (j != imax)
        {
            for (k = 0; k < n; k++)
            {
                dum = matrix_a[imax][k];
                matrix_a[imax][k] = matrix_a[j][k];
                matrix_a[j][k] = dum;
            }

            d = -(d);
            vv[imax] = vv[j];
        }

        indx[j] = imax;

        if (matrix_a[j][j] == 0.0)
            matrix_a[j][j] = TINY;

        if (j != n)
        {
            dum = 1.0 / matrix_a[j][j];
            for (i = j+1; i < n; i++)
                matrix_a[i][j] *= dum;
        }
        
    }

    return matrix_a;
}

void MinimosQuadrados::methodLU_Backsubstitution(matrix matrix_a, double *B, int *INDX, int n)
{
    int II = -1, LL;
    double sum = 0.0;	
	
    for (int i = 0; i < n; i++)
    {
        LL = INDX[i];
        sum = B[LL];
        B[LL] = B[i];

        if (II >= 0)
            for (int j = II; j < i; j++)
            {
                sum -= matrix_a[i][j] * B[j];
            }
        else
            if (sum) {
                II = i;
            }
		
        B[i] = sum;
    }
	
    for (int i = n-1; i >= 0; i--)
    {
        sum = B[i];
        for (int j = i+1; j < n; j++)
            sum -= matrix_a[i][j] * B[j];

        B[i] = sum / matrix_a[i][i];
    }

    return;
}

std::vector<double> MinimosQuadrados::calcular()
{
    vector<double> matrix_x = curve.getElementsX();
    vector<double> matrix_y = curve.getElementsY();

    vector<double> mulXY = MinimosQuadrados::somatorioXmulY(matrix_x, matrix_y);
    vector<double> soma_x = somatorioPotenciaX(matrix_x);
	
    /**
      * Montar matriz que contêm os somatórios das potencias de x
      */
    int aux = 0;
    matrix matrix_a;
    matrix_a.resize(graupolin+1);

    for (int i = 0; i < (graupolin+1); i++)
        matrix_a[i].resize(graupolin+1);

    for (int i = 0; i <= graupolin; i++)
    {
        for (int j = 0; j <= graupolin; j++)
        {
            matrix_a[i][j] = 0.0;
            aux = j + i;
            matrix_a[i][j] = soma_x[aux];
        }
    }

    int *INDX = new int[graupolin+1];
    double *B = new double[graupolin+1];
	
    for (unsigned int i = 0; i < mulXY.size(); i++)
        B[i] = mulXY[i];
	
    matrix_a = methodLU_Decomposition(matrix_a, graupolin+1, INDX);
    methodLU_Backsubstitution(matrix_a, B, INDX, graupolin+1);

    vector<double> c(graupolin+1);

    for (int i = 0; i < graupolin+1; i++)
            c[i] = B[i];

    /* Cálculo do Coeficiente de Correlação */
    double soma_y = 0.0;
    double soma_y2 = 0.0;
    double somay_correlacao = 0.0;
    vector<double> yesperado(matrix_y.size());

    for (unsigned int i = 0; i < matrix_y.size(); i++)
    {
        soma_y += matrix_y[i];
        soma_y2 += pow(matrix_y[i], 2);

        yesperado[i] = 0.0;
        for (int j = 0; j < (graupolin + 1); j++)
            yesperado[i] += c[j] * pow(matrix_x[i], j);

        somay_correlacao += pow(matrix_y[i] - yesperado[i], 2);
    }

    double r2 = 0.0;
    double r = 0.0;

    r2 = 1.0 - (somay_correlacao/(soma_y2 - pow(soma_y, 2)/(double)matrix_y.size()));

    if (r2 < 0)
        throw std::string("coeficiente de correlação menor que zero");
    else
        r = sqrt(r2);

    coef_correlacao = r;
    
    delete[] INDX;
    delete[] B;
	
    return c;
}
