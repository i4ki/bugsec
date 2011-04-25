#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>
#include "plotcurve.h"

class QwtPlotCurve;

class Plot : public QwtPlot
{
public:
    Plot(QWidget* parent = 0);
    Plot(std::vector<PlotCurve *> _cCurves, QWidget* parent = 0);
    Plot(std::vector<PlotCurve *> _cCurves, std::vector<PlotCurve *> _cPoints, QWidget *parent);
    ~Plot();
    void setProjectTitle(const QString& title);
    void setEquationName(const QString& name);
    void setNrPoints(int nr) { nrPoints = nr; }
    void createGraph();

protected:
    std::vector<PlotCurve *> cCurves;
    std::vector<PlotCurve *> cPoints;
    int nrPoints;
};

#endif // PLOT_H
