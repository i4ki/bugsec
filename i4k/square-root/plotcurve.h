#ifndef PLOTCURVE_H
#define PLOTCURVE_H

#include "qwt_plot_curve.h"
#include <vector>

class Curve;

class PlotCurve : public QwtPlotCurve
{
public:
    PlotCurve();
    ~PlotCurve();
    void initializePoints();
    void setProjectTitle(const QString& text);
    void setCoeficientes(std::vector<double>* _c);
    void setCoeficientesCorrelacao(double _coef_corr);
    void setExperimentalPoints(Curve* _c);
    void setColorCurve(int color);
    void setColorPoints(int color);
    Curve* getCurve() const { return curve; }
    void plotGraph();
    void plotExperimentalPoints();

protected:
    double *x;
    double *y;
    std::vector<double> *c;
    double coef_corr;
    Curve* curve;
    QwtPlot* plot;
    int colorPoint;
    int colorCurve;
};

#endif // PLOTCURVE_H
