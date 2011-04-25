#ifndef WIZARD_H
#define WIZARD_H
#include <QWizard>
#include <vector>
#include "algorithm/curve.h"

class ConfigInitialPage;

class Wizard : public QWizard
{
    Q_OBJECT

public:
    Wizard(QWidget* parent, std::vector<std::vector<double> > *all_coef, std::vector<double> *all_coef_correlacao, std::vector<Curve> *points);
    void accept();
    ~Wizard();

protected:
    ConfigInitialPage* configInitialPage;
    std::vector<std::vector<double> > *all_coeficientes;
    std::vector<double> *all_coef_correlacao;
    std::vector<Curve> *_curves;
};

#endif // WIZARD_H
