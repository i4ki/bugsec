#include "plotcurve.h"
#include <qwt_symbol.h>
#include "algorithm/curve.h"
#include "polinomial.h"
#include <iostream>
#include <cmath>

PlotCurve::PlotCurve()
    : QwtPlotCurve()
    , colorPoint(0)
    , colorCurve(0)
{

#if QT_VERSION >= 0x040000
    setRenderHint(QwtPlotItem::RenderAntialiased);
#endif

}

PlotCurve::~PlotCurve()
{
    delete[] x;
    delete[] y;
}

void PlotCurve::initializePoints()
{

}

void PlotCurve::setProjectTitle(const QString &text)
{
    setTitle(text);
}

void PlotCurve::setCoeficientes(std::vector<double>* _c)
{
    c = _c;
}

void PlotCurve::setCoeficientesCorrelacao(double _coef_corr)
{
    coef_corr = _coef_corr;
}

void PlotCurve::setExperimentalPoints(Curve* _c)
{
    curve = _c;
}

void PlotCurve::setColorCurve(int color)
{
   colorCurve = color;
}

void PlotCurve::setColorPoints(int color)
{
    colorPoint = color;
}

void PlotCurve::plotGraph()
{
    setStyle(QwtPlotCurve::Lines);

    QwtSymbol sym;

    switch (colorCurve)
    {
    case Qt::red:
        setPen(QColor(Qt::red));
        break;
    case Qt::blue:
        setPen(QColor(Qt::blue));
        break;
    case Qt::green:
        setPen(QColor(Qt::green));
        break;
    default:
        setPen(QColor(Qt::green));
    }

    Polinomial poly;

    std::vector<double> matrix_x = curve->getElementsX();

    poly.setCoeficientes(*c);

    double minX = matrix_x[0];
    double maxX = matrix_x[1];

    for (unsigned int i = 0; i < matrix_x.size(); i++)
    {
        if (minX > matrix_x[i])
            minX = matrix_x[i];

        if (maxX < matrix_x[i])
            maxX = matrix_x[i];
    }

    QString minXStr = QString("%1").arg(minX);
    if (minX < 0)
        minXStr.remove(0, 1);

    int countDigits = 0;
    bool isFracao = false;
    for (int i = 0; i < minXStr.length(); i++)
    {
        if (minXStr.at(i) != QChar('.'))
            ++countDigits;
        else
            isFracao = true;
    }

    QString stepStr = QString("");

    for (int i = 0; i < countDigits-1; i++)
    {
        stepStr += QString("0");
    }

    if (fabs(minX) < 1 && fabs(minX) > 0)
    {
        stepStr.insert(1, QString("."));
        stepStr += QString("1");
    } else {
        stepStr.prepend(QString("1"));
    }

    double step = stepStr.toDouble();

    int nrPoints = 1000;

    x = new double[nrPoints];
    y = new double[nrPoints];

    for (int i = 0; i < nrPoints; i++)
    {
        x[i] = (i * step/100 + minX);
        y[i] = (poly.polinomy(x[i]));
    }

    setData(x, y, nrPoints);
}

void PlotCurve::plotExperimentalPoints()
{
    setStyle(QwtPlotCurve::NoCurve);

    QwtSymbol sym;

    switch (colorPoint)
    {
    case Qt::darkRed:
        sym.setPen(QColor(Qt::darkRed));
        break;
    case Qt::darkBlue:
        sym.setPen(QColor(Qt::darkBlue));
        break;
    case Qt::darkGreen:
        sym.setPen(QColor(Qt::darkGreen));
        break;
    }

    sym.setStyle(QwtSymbol::Cross);
    sym.setSize(QSize(10, 10));

    //setStyle(QwtPlotCurve::UserCurve);
    setSymbol(sym);

    std::vector<double> matrix_x = curve->getElementsX();
    std::vector<double> matrix_y = curve->getElementsY();

    int nrPoints = matrix_x.size();

    x = new double[nrPoints];
    y = new double[nrPoints];

    for (int i = 0; i < nrPoints; i++)
    {
        x[i] = matrix_x[i];
        y[i] = matrix_y[i];
    }

    setData(x, y, nrPoints);
}


