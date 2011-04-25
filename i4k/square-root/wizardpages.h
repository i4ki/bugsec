#ifndef WIZARDPAGES_H
#define WIZARDPAGES_H

#include "algorithm/curve.h"
#include <QWizardPage>
#include <QFile>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QGroupBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <iostream>
#include <vector>

class IntroPage : public QWizardPage
{
    Q_OBJECT
public:
    IntroPage(QWidget* parent = 0);
    ~IntroPage();

protected:
    QLabel* introLbl;

};

class ConfigInitialPage : public QWizardPage
{
    Q_OBJECT
public:
    ConfigInitialPage(QWidget* parent = 0);
    ~ConfigInitialPage();
    void _atentionXYValues();
    virtual bool isComplete() const;
    int getGrauPolin() const;
    std::vector<Curve> getCurves() const { return curves; }

protected:
    bool parseImportFile(const QString& content);
    bool _parseImportFile(const QStringList& points);
    bool _getPoints(const QString& points);

    /*
     * Váriaveis de Configuração
     */
    std::vector<Curve> curves;
    int grauPolin;
    int nrCurves;
    QString unitX;
    QString unitY;
    QString importFileName;

    /*
     * Váriaveis da Interface Gráfica
     */
    QFile* importFile;
    QLabel* label1;
    QLabel* label2;
    QLabel* label3;
    QLabel* label4;
    QLabel* label5;
    QLabel* label6;

    QPushButton* verBtn;
    QPushButton* openFileBtn;
    QPushButton* insertDataBtn;
    QSpinBox* nrCurvaSpin;
    QSpinBox* grauPolinSpin;
    QDialog* dialogInsertData;
    QLineEdit* unitXEdit;
    QLineEdit* unitYEdit;
    QRadioButton* importRadio;
    QRadioButton* insertRadio;
    QGroupBox* groupDados;
    QVBoxLayout* vImportLayout;
    QVBoxLayout* vInsertLayout;
    QVBoxLayout* vGlobalLayout;
    std::vector<QTableWidget *> tableWidgets;

protected slots:
    void changeRadio();
    void openFileForImport();
    void verFormatacaoDialog();
    void insertExperimentalData();
    void addRowInTable();
    void okThenGetExperimentalPoints();
    void currentItemTableChanged(QTableWidgetItem *item);
};

#endif // WIZARDPAGES_H
