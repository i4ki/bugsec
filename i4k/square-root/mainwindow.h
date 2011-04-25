#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QAction>
#include <QMenu>
#include <QLabel>
#include "algorithm/curve.h"
#include <vector>
#include <qwt_plot.h>
#include "plot.h"

namespace Ui
{
    class Form;
}


class Wizard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void createNewProject();
    void viewInformationCalculated();
    void setMenuData();
    void viewExperimentalPoints();
    void printGraph();
    void graph();
    void aboutDialog();
    void runGraph();

protected:
    void createActions();
    void createMenus();
    QString generateStringFunction(std::vector<double> c);

    /* Ações */
    QAction* newProjectAction;
    QAction* exportProjectAction;
    QAction* exitAction;
    QAction* aboutAction;
    QAction* curve1Action;
    QAction* printAction;

    /* Menus */
    QMenu* fileMenu;
    QMenu* dataMenu;
    QMenu* helpMenu;

    /* Dialogs */
    QDialog* dialogInfoPoints;
    QLabel* labelTest;
    QLabel* labelUFSC;
    Plot* plot;

    /* Wizard */
    Wizard* wiz;

    std::vector<std::vector<double> > *all_coeficientes;
    std::vector<double> *all_coef_correlacao;
    std::vector<Curve> *curves;

    int idx;

};

#endif // MAINWINDOW_H
