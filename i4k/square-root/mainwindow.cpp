#include "mainwindow.h"
#include "algorithm/minimosquadrados.h"
#include <QStatusBar>
#include <QMenuBar>
#include <QMessageBox>
#include <QImageReader>
#include <QInputDialog>
#include <QDialog>
#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QPushButton>
#include <QPrinter>
#include <QPrintDialog>
#include <QLabel>
#include "actioncurve.h"
#include "wizard.h"
#include "plot.h"
#include "plotcurve.h"
#include "polinomial.h"
#include "about.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , plot(NULL)
    , all_coeficientes(new std::vector<std::vector<double> >())
    , all_coef_correlacao(new std::vector<double>())
    , curves(new std::vector<Curve>())
{
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    createActions();
    createMenus();

    labelUFSC = new QLabel(this);
    labelUFSC->setPixmap(QPixmap(QString(":/images/logo/brasao1.png")));
    labelUFSC->setAlignment(Qt::AlignCenter);
    setCentralWidget(labelUFSC);

    setMinimumSize(800, 600);
    statusBar();
}

MainWindow::~MainWindow()
{
    delete curves;
    delete all_coeficientes;
    delete all_coef_correlacao;
    if (plot)
    	delete plot;
}

void MainWindow::createActions()
{
    newProjectAction = new QAction(tr("Novo Projeto"), this);
    newProjectAction->setStatusTip(tr("Novo Projeto"));
    newProjectAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    connect(newProjectAction, SIGNAL(triggered()), this, SLOT(createNewProject()));

    exportProjectAction = new QAction(tr("exportar"), this);
    exportProjectAction->setStatusTip(tr("Exportar gráfico"));
    connect(exportProjectAction, SIGNAL(triggered()), this, SLOT(exportProject()));

    printAction = new QAction(tr("Imprimir"), this);
    printAction->setStatusTip(tr("Imprimir gráfico"));
    printAction->setEnabled(false);
    connect(printAction, SIGNAL(triggered()), this, SLOT(printGraph()));

    exitAction = new QAction(tr("Sair"), this);
    exitAction->setStatusTip(tr("Sair do programa"));
    exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F4));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));


    curve1Action = new QAction(tr("Curva 1"), this);
    curve1Action->setEnabled(false);

    aboutAction = new QAction(tr("Sobre"), this);
    aboutAction->setStatusTip(tr("Sobre"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutDialog()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("Arquivo"));
    fileMenu->addAction(newProjectAction);
//    fileMenu->addAction(exportProjectAction);
    fileMenu->addAction(printAction);
    fileMenu->addAction(exitAction);

    dataMenu = menuBar()->addMenu(tr("Dados"));
    dataMenu->addAction(curve1Action);

    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::createNewProject()
{
    wiz = new Wizard(this, all_coeficientes, all_coef_correlacao, curves);
    wiz->show();
    connect(wiz, SIGNAL(accepted()), this, SLOT(runGraph()));
}

void MainWindow::runGraph()
{
    setMenuData();
    graph();
}

void MainWindow::setMenuData()
{
    dataMenu->clear();
    idx = 0;

    for (unsigned int i = 0; i < all_coeficientes->size(); i++)
    {
        idx = i;
        QMenu* curveMenu = dataMenu->addMenu(tr("Curva %1").arg(i+1));
        ActionCurve* dataAction = new ActionCurve(tr("Pontos Experimentais"), this);
        dataAction->setIdx(i);
        dataAction->setStatusTip(tr("Pontos Experimentais da curva %1").arg(i+1));
        connect(dataAction, SIGNAL(triggered()), this, SLOT(viewExperimentalPoints()));
        curveMenu->addAction(dataAction);
      //  connect(okBtn, SIGNAL(clicked()), dialogInsertData, SLOT(close()));
    }
}

void MainWindow::viewExperimentalPoints()
{
    int idx = qobject_cast<ActionCurve *>(sender())->getIdx();
    QDialog* dialog = new QDialog(this);
    QVBoxLayout* vbox1 = new QVBoxLayout;

    std::vector<double> matrix_x = curves->at(idx).getElementsX();
    std::vector<double> matrix_y = curves->at(idx).getElementsY();
    std::vector<double> coef = all_coeficientes->at(idx);

    QLabel* pointLbl = new QLabel(tr("Pontos Experimentais"), dialog);
    vbox1->addWidget(pointLbl, 0, Qt::AlignCenter | Qt::AlignTop);

    QTableView* viewPoints = new QTableView(dialog);
    QStandardItemModel* modelPoints = new QStandardItemModel(matrix_x.size(), 2, dialog);
    for (unsigned int j = 0; j < matrix_x.size(); j++)
    {
        QStandardItem* item = new QStandardItem(tr("%1").arg(matrix_x[j]));
        item->setTextAlignment(Qt::AlignCenter);
        modelPoints->setItem(j, 0, item);
    }

    for (unsigned int j = 0; j < matrix_y.size(); j++)
    {
        QStandardItem* item = new QStandardItem(tr("%1").arg(matrix_y[j]));
        item->setTextAlignment(Qt::AlignCenter);
        modelPoints->setItem(j, 1, item);
    }

    QStringList headersPoints;
    headersPoints << "x" << "y";

    modelPoints->setHorizontalHeaderLabels(headersPoints);
    viewPoints->setModel(modelPoints);
    viewPoints->resizeColumnsToContents();
    viewPoints->resizeRowsToContents();

    int column1 = viewPoints->columnWidth(0);
    int column2 = viewPoints->columnWidth(1);
    int rownSize = viewPoints->rowHeight(0);
    viewPoints->setFixedWidth(column1+column2+20);
    viewPoints->setFixedHeight(rownSize * matrix_x.size() + rownSize+6);

    vbox1->addWidget(viewPoints, 0, Qt::AlignCenter);

    QPushButton* okBtn = new QPushButton(tr("OK"), this);
    connect(okBtn, SIGNAL(clicked()), dialog, SLOT(close()));

    QHBoxLayout* hbox = new QHBoxLayout;
    hbox->addSpacing(10);
    hbox->addWidget(okBtn);
//    hbox->addWidget(printBtn);
    hbox->addSpacing(10);

    vbox1->addLayout(hbox);

    dialog->setLayout(vbox1);
    dialog->show();
}


/**
  @deprecated
 */
void MainWindow::viewInformationCalculated()
{
//    all_coeficientes
//    all_coef_correlacao
//    curves

    dialogInfoPoints = new QDialog(this);
    QVBoxLayout* vbox = new QVBoxLayout;
    QVBoxLayout* vbox1 = new QVBoxLayout();
    QVBoxLayout* vbox2 = new QVBoxLayout;

    QLabel* labelTitle = new QLabel(tr("<b>Valores Calculados</b>"), dialogInfoPoints);
    vbox->addWidget(labelTitle);

    for (unsigned int i = 0; i < curves->size(); i++)
    {
        std::vector<double> matrix_x = curves->at(i).getElementsX();
        std::vector<double> matrix_y = curves->at(i).getElementsY();
        std::vector<double> coef = all_coeficientes->at(i);

        QHBoxLayout* hbox = new QHBoxLayout;

        QLabel* pointLbl = new QLabel(tr("Pontos Experimentais"), dialogInfoPoints);
        vbox1->addWidget(pointLbl);
        QLabel* coefLbl = new QLabel(tr("Calculados"), dialogInfoPoints);
        vbox2->addWidget(coefLbl, 0, Qt::AlignCenter);

        QTableView* viewPoints = new QTableView(dialogInfoPoints);
        QStandardItemModel* modelPoints = new QStandardItemModel(matrix_x.size(), 2, dialogInfoPoints);
        for (unsigned int j = 0; j < matrix_x.size(); j++)
        {
            QStandardItem* item = new QStandardItem(tr("%1").arg(matrix_x[j]));
            item->setTextAlignment(Qt::AlignCenter);
            modelPoints->setItem(j, 0, item);
        }

        for (unsigned int j = 0; j < matrix_y.size(); j++)
        {
            QStandardItem* item = new QStandardItem(tr("%1").arg(matrix_y[j]));
            item->setTextAlignment(Qt::AlignCenter);
            modelPoints->setItem(j, 1, item);
        }

        QStringList headersPoints;
        headersPoints << "x" << "y";

        modelPoints->setHorizontalHeaderLabels(headersPoints);
        viewPoints->setModel(modelPoints);
        viewPoints->resizeColumnsToContents();
        viewPoints->resizeRowsToContents();

        int column1 = viewPoints->columnWidth(0);
        int column2 = viewPoints->columnWidth(1);
        int rownSize = viewPoints->rowHeight(0);
        viewPoints->setFixedWidth(column1+column2+20);
        viewPoints->setFixedHeight(rownSize * matrix_x.size() + rownSize+6);

        vbox1->addWidget(viewPoints);

        QVBoxLayout* _vbox1 = new QVBoxLayout;

        QString coefStr;
        QString coefCorr;
        QString labelStr1 = QString("Polinomio ajustador com os coeficientes: ");
        QString labelStr2 = QString("coeficiente de correlação: ");

//        coefStr = generateStringFunction(coef);

        QLabel* coefLbl2 = new QLabel(labelStr1, dialogInfoPoints);
        _vbox1->addWidget(coefLbl2);
        QLabel* coefLbl3 = new QLabel(tr("<b>") + coefStr + tr("</b>"), dialogInfoPoints);
        _vbox1->addWidget(coefLbl3);

        coefCorr.append(QString("%1").arg(all_coef_correlacao->at(i)));

        QLabel* coefCorrLbl = new QLabel(labelStr2 + coefCorr, dialogInfoPoints);
        _vbox1->addWidget(coefCorrLbl);
        _vbox1->addSpacing(120);

        vbox2->addLayout(_vbox1);

        hbox->addLayout(vbox1);
        hbox->addLayout(vbox2);
        vbox->addLayout(hbox);
    }

    QPushButton* okBtn = new QPushButton(tr("OK"), dialogInfoPoints);
    connect(okBtn, SIGNAL(clicked()), this, SLOT(graph()));

    QHBoxLayout* hBtnLay = new QHBoxLayout;
    hBtnLay->addWidget(okBtn, 0, Qt::AlignCenter);

    vbox->addSpacing(20);
    vbox->addLayout(hBtnLay);
    dialogInfoPoints->setLayout(vbox);
    dialogInfoPoints->setContentsMargins(20, 20, 20, 20);

    dialogInfoPoints->show();
}

void MainWindow::graph()
{


    int colorsCurve[] = {
        Qt::red,
        Qt::blue,
        Qt::green,        
    };

    int colorsPoints[] = {
        Qt::darkRed,
        Qt::darkBlue,
        Qt::darkGreen
    };

    std::vector<PlotCurve *> cCurves;
    std::vector<PlotCurve *> cPoints;
    unsigned int size = all_coeficientes->size();
    for (unsigned int i = 0; i < size; i++)
    {
        PlotCurve* cCurve = new PlotCurve();
        cCurve->setCoeficientes(&all_coeficientes->at(i));
        cCurve->setCoeficientesCorrelacao(all_coef_correlacao->at(i));
        cCurve->setExperimentalPoints(&curves->at(i));
        cCurve->setProjectTitle(tr("Curva %1").arg(i+1));
        cCurve->setColorCurve(colorsCurve[i]);
        cCurves.push_back(cCurve);

        PlotCurve* cPoint = new PlotCurve();
        cPoint->setExperimentalPoints(&curves->at(i));
        cPoint->setProjectTitle(tr("Pontos experimentais"));
        cPoint->setColorPoints(colorsPoints[i]);
        cPoints.push_back(cPoint);
    }

    plot = new Plot(cCurves, cPoints, this);
    plot->setProjectTitle(tr("Minimos Quadrados"));
    plot->createGraph();    
    plot->resize(800, 600);
    plot->show();

    QWidget* central = new QWidget(this);

    QHBoxLayout* hbox = new QHBoxLayout;
    QFrame* legenda = new QFrame(this);
    legenda->setFixedWidth(200);
    legenda->setFrameShape(QFrame::WinPanel);

    QVBoxLayout* vboxLegenda = new QVBoxLayout;

    QLabel* titleLbl = new QLabel(tr("<b>Coeficientes</br>"), legenda);
    titleLbl->setAlignment(Qt::AlignCenter);
    titleLbl->setWordWrap(true);

    vboxLegenda->addWidget(titleLbl, 0, Qt::AlignTop);

    for (unsigned int i = 0; i < all_coeficientes->size(); i++)
    {
        QFrame* frame = new QFrame(legenda);
        QVBoxLayout* layFrame = new QVBoxLayout;

        QString color;

        switch (i)
        {
        case 0:
            color = "red";
            break;
        case 1:
            color = "blue";
            break;
        case 2:
            color = "green";
            break;
        }

        QLabel* curveLbl = new QLabel(tr("<span style='color: %1'>Curva %2</b>").arg(color).arg(i+1), frame);
        layFrame->addWidget(curveLbl, 0, Qt::AlignTop | Qt::AlignCenter);

        for (unsigned int j = 0; j < all_coeficientes->at(i).size(); j++)
        {
            QString msg = QString("a[%1] = %2").arg(j);
            double value = all_coeficientes->at(i).at(j);

            msg = msg.arg(value);

            QLabel* aLbl = new QLabel(msg, frame);
            layFrame->addWidget(aLbl, 0, Qt::AlignCenter | Qt::AlignTop);
        }
        QLabel* coefLabel = new QLabel(tr("Correlaçao: %1").arg(all_coef_correlacao->at(i)), frame);
        coefLabel->setAlignment(Qt::AlignCenter | Qt::AlignTop);
        layFrame->addWidget(coefLabel, 0, Qt::AlignCenter | Qt::AlignTop);

        frame->setLayout(layFrame);
        vboxLegenda->addWidget(frame, 0, Qt::AlignTop);
    }

    vboxLegenda->addSpacing(600);

    legenda->setLayout(vboxLegenda);
    legenda->show();
    hbox->addWidget(legenda);

    hbox->addWidget(plot);
    central->setLayout(hbox);
    setCentralWidget(central);

    printAction->setEnabled(true);
}

void MainWindow::printGraph()
{
    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog* printDialog = new QPrintDialog(&printer, this);
    printDialog->setWindowTitle(tr("Imprimir Gráfico"));
    printDialog->show();

    if (printDialog->exec() == QDialog::Accepted)
    {
        QwtPlotPrintFilter filter;
        filter.setOptions(QwtPlotPrintFilter::PrintAll);
        plot->print(printer, filter);
    }

    delete printDialog;
}

// TODO
/*
QString MainWindow::generateStringFunction(std::vector<double> c)
{
    QString function = QString("f(x) = ");
    QString x = "";


    for (unsigned int i = 1; i < c.size(); i++)
    {
        if (c[i] < 1.0e-19)
            continue;
        else
            x.append(QString("%1x^%2").arg(c[i]).arg(i));


        if (i == 1)
        {
            if (c[i] < 0)            
                x.append(QString("%1").arg(c[0]));
            else
                x.append(QString("%1+").arg(c[0]));
        }

        if (i < (c.size()-1))
        {
            if (c[i+1] >= 0)
                x.append(tr("+"));
        }        
    }

    if (c[0] > 1.0e-19)
    {
        if (c.size() > 1 && c[1] >= 0)
            x.prepend(QString("%1+").arg(c[0]));
        else
            x.prepend(QString("%1").arg(c[0]));
    }

    function.append(x);

    return function;
}

*/

void MainWindow::aboutDialog()
{
    About* about = new About(this);
    about->show();
}
