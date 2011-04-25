#include <qapplication.h>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_data.h>
#include <qwt_text.h>
#include <qwt_math.h>
#include <qwt_symbol.h>
#include <math.h>

//-----------------------------------------------------------------
//              simple.cpp
//
//      A simple example which shows how to use QwtPlot and QwtData
//-----------------------------------------------------------------

class SimpleData: public QwtData
{
    // The x values depend on its index and the y values
    // can be calculated from the corresponding x value. 
    // So we don´t need to store the values.
    // Such an implementation is slower because every point 
    // has to be recalculated for every replot, but it demonstrates how
    // QwtData can be used.

public:
    SimpleData(double(*y)(double), size_t size):
        d_size(size),
        d_y(y)
    {
    }

    virtual QwtData *copy() const
    {
        return new SimpleData(d_y, d_size);
    }

    virtual size_t size() const
    {
        return d_size;
    }

    virtual double x(size_t i) const
    {
        return 0.01 * i;
    }

    virtual double y(size_t i) const
    {
        return d_y(x(i));
    }
private:
    size_t d_size;
    double(*d_y)(double);
};

class Plot : public QwtPlot
{
public:
    Plot(QWidget *parent = 0);
    double static quadFunc(double x) { return x*x; }
};

Plot::Plot(QWidget *parent)
    : QwtPlot(parent)
{
    setTitle("Cálculo dos");
    insertLegend(new QwtLegend(), QwtPlot::RightLegend);

    // Set axis titles
    setAxisTitle(xBottom, "x -->");
    setAxisTitle(yLeft, "y -->");
    
    // Insert new curves
    QwtPlotCurve *cSin = new QwtPlotCurve("y = sin(x)");
#if QT_VERSION >= 0x040000
    cSin->setRenderHint(QwtPlotItem::RenderAntialiased);
#endif
    cSin->setPen(QPen(Qt::red));
    cSin->attach(this);

    QwtSymbol sym;

    sym.setPen(QColor(Qt::red));
    sym.setStyle(QwtSymbol::Cross);
    sym.setSize(QSize(2,2));

    // Create sin and cos data
    const int nPoints = 1000;
    setAxisScale(QwtPlot::yLeft, 0, 100, 10);
    setAxisScale(QwtPlot::xBottom, 0, 10, 1);
    cSin->setStyle(QwtPlotCurve::NoCurve);
    cSin->setSymbol(sym);
    cSin->setData(SimpleData(&Plot::quadFunc, nPoints));

}
