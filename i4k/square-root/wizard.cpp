#include "wizard.h"
#include "wizardpages.h"
#include "algorithm/curve.h"
#include "algorithm/minimosquadrados.h"
#include <QDebug>

Wizard::Wizard(QWidget *parent, std::vector<std::vector<double> > *all_coef, std::vector<double> *all_coef_corr, std::vector<Curve>* curves)
    : QWizard(parent)
{
    all_coeficientes = all_coef;
    all_coef_correlacao = all_coef_corr;
    _curves = curves;

    setAttribute(Qt::WA_DeleteOnClose);

    configInitialPage = new ConfigInitialPage;
    addPage(new IntroPage);
    addPage(configInitialPage);

    setWindowTitle(tr("Mínimos Quadrados"));
    setWizardStyle(QWizard::ClassicStyle);
}

Wizard::~Wizard()
{

}

void Wizard::accept()
{
    int graupolin = configInitialPage->getGrauPolin();
    std::vector<Curve> curves = configInitialPage->getCurves();

    if (!curves.empty())
    {
        all_coeficientes->clear();
        all_coef_correlacao->clear();
        _curves->clear();

        try {

            for (unsigned int i = 0; i < curves.size(); i++)
            {
                _curves->push_back(curves[i]);

                MinimosQuadrados minQuad;
                minQuad.setGrauPolin(graupolin);

                Curve crv = curves[i];
                minQuad.setExperimentalData(crv);

                std::vector<double> c(graupolin+1);

                c = minQuad.calcular();
                all_coeficientes->push_back(c);
                all_coef_correlacao->push_back(minQuad.getCoefCorrelacao());
            }
        } catch (std::string e)
        {
            qDebug() << "ERRO";
        }
    }

    QDialog::accept();
}
