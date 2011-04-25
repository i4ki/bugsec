#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_symbol.h>
#include <qwt_text_engine.h>
#include <qwt_scale_engine.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "polinomial.h"
#include "algorithm/curve.h"
#include "plot.h"

Plot::Plot(QWidget *parent)
    : QwtPlot(parent)
    , nrPoints(0)
{

}

Plot::Plot(std::vector<PlotCurve *> _cCurves, QWidget *parent)
    : QwtPlot(parent)
    , cCurves(_cCurves)
    , nrPoints(0)
{

}

Plot::Plot(std::vector<PlotCurve *>_cCurves, std::vector<PlotCurve *>_cPoints, QWidget *parent)
    : QwtPlot(parent)
    , cCurves(_cCurves)
    , cPoints(_cPoints)
    , nrPoints(0)
{

}

Plot::~Plot()
{
    for (unsigned int i = 0; i < cCurves.size(); i++)
        delete cCurves.at(i);

    for (unsigned int i = 0; i < cPoints.size(); i++)
        delete cPoints.at(i);
}

void Plot::setProjectTitle(const QString &title)
{
    setTitle(title);
}

void Plot::createGraph()
{
    insertLegend(new QwtLegend(), QwtPlot::BottomLegend);

    setAxisTitle(xBottom, "x -->");
    setAxisTitle(yLeft, "y -->");

    // Inicializa as variaveis pela primeira curva

    Curve* curve = cCurves[0]->getCurve();
    std::vector<double> matrix_x = curve->getElementsX();
    std::vector<double> matrix_y = curve->getElementsY();

    double minX = matrix_x[0];
    double maxX = matrix_x[0];
    double minY = matrix_y[0];
    double maxY = matrix_y[0];

    for (unsigned int i = 0; i < cCurves.size(); i++)
    {
        Curve* curve = cCurves[i]->getCurve();
        std::vector<double> matrix_x = curve->getElementsX();
        std::vector<double> matrix_y = curve->getElementsY();

        for (unsigned int j = 0; j < matrix_x.size(); j++)
        {
            if (minX > matrix_x[j])
                minX = matrix_x[j];

            if (maxX < matrix_x[j])
                maxX = matrix_x[j];

            if (minY > matrix_y[j])
                minY = matrix_y[j];

            if (maxY < matrix_y[j])
                maxY = matrix_y[j];
        }

        cCurves[i]->attach(this);
        cCurves[i]->plotGraph();

        cPoints[i]->attach(this);
        cPoints[i]->plotExperimentalPoints();

    }

    int py = (maxY - minY) / 10;
    int px = (maxX - minX) / 10;
    minX -= px;
    maxX += px;
    minY -= py;
    maxY += py;

    int stepY = (maxY - minY)/10;
    int stepX = (maxX - minX)/10;

//    QwtLog10ScaleEngine* logScale = new QwtLog10ScaleEngine();
//    setAxisScaleEngine(QwtPlot::xBottom, logScale);
//    setAxisScaleEngine(QwtPlot::yLeft, logScale);


    setAxisScale(QwtPlot::xBottom, minX, maxX, stepX);
    setAxisScale(QwtPlot::yLeft, minY, maxY, stepY);


    replot();
}
