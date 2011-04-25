#include "wizardpages.h"
#include <QDoubleValidator>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QIcon>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLineEdit>
#include <QDebug>
#include "algorithm/point.h"
#include "algorithm/minimosquadrados.h"
/**
  * Página de Introdução
  */
IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Cálculo dos Mínimos Quadrados"));

    setPixmap(QWizard::WatermarkPixmap, QPixmap(QString(":/images/logo/einstein.png")));

    introLbl = new QLabel(
    	tr("\nAs próximas telas lhe auxiliarão a calcular a melhor curva polinomial "
        	 "para o ajuste de seus pontos experimentais, através do método dos "
        	 "Mínimos Quadrados.\n ")
    	+ tr("Será possível fazer um ajuste polinomial de no máximo sexto grau.\n ")
    	+ tr("Além dos coeficientes do polinômio o programa fornecerá o "
    		 "coeficiente de correlação, para que o usuário verifique o quão bom é "
    		 "seu ajuste, e por final será apresentado o gráfico do polinômio "
    		 "junto com os pontos experimentais.\n")
    	+ tr("O usuário poderá também escolher o número de curvas, no máximo "
    		 "três, para plotar em um mesmo gráfico, observando que as três curvas "
    		 "terão o mesmo grau e as mesmas unidades. " )
    
    , this);

    introLbl->setWordWrap(true);

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(introLbl);
    setLayout(vbox);
}

IntroPage::~IntroPage() {}

/**
  * Página de Configuração Inicial
  */
ConfigInitialPage::ConfigInitialPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Configurações Iniciais"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(QString(":/images/logo/jazz.png")));
    setButtonText(QWizard::FinishButton, tr("Calcular"));

    QVBoxLayout* vbox = new QVBoxLayout;

    label1 = new QLabel(tr("Quantas curvas voce deseja calcular?"), this);
    label2 = new QLabel(tr("Qual o grau para o ajuste polinomial?"), this);
    label6 = new QLabel(tr("Qual o tipo de escala?"), this);

    QString pergunta3Str;
    pergunta3Str.append(
            tr("\nPara a entrada dos pontos experimentais você pode importar ")
            + tr("um arquivo de texto, com uma formatação específica, ou pode ")
            + tr("inserir os pontos através do teclado."));

    label3 = new QLabel(pergunta3Str, this);
    label3->setWordWrap(true);

    groupDados = new QGroupBox(tr("Inserir dados experimentais"), this);
    groupDados->setFlat(true);

    vGlobalLayout = new QVBoxLayout;
    vImportLayout = new QVBoxLayout;
    vInsertLayout = new QVBoxLayout;

    importRadio = new QRadioButton(tr("Importar de um arquivo"), this);
    insertRadio = new QRadioButton(tr("Inserir através do teclado"), this);
    insertRadio->setChecked(true);
    connect(importRadio, SIGNAL(clicked()), this, SLOT(changeRadio()));
    connect(insertRadio, SIGNAL(clicked()), this, SLOT(changeRadio()));

    vGlobalLayout->addWidget(insertRadio);
    vGlobalLayout->addWidget(importRadio);

    /*
     * Layout para o arquivo a ser importado
     */
    openFileBtn = new QPushButton(tr("Importar arquivo"), this);
    openFileBtn->setFixedWidth(120);
    openFileBtn->setVisible(false);
    connect(openFileBtn, SIGNAL(clicked()), this, SLOT(openFileForImport()));
    QHBoxLayout* hboxImport = new QHBoxLayout;
    hboxImport->addWidget(openFileBtn, 0, Qt::AlignLeft);
//    hboxImport->addWidget(label4, 0, Qt::AlignLeft);
    hboxImport->addSpacing(200);

    verBtn = new QPushButton(tr("Ver formatação"), this);
    verBtn->setFixedWidth(120);
    verBtn->setVisible(false);
    connect(verBtn, SIGNAL(clicked()), this, SLOT(verFormatacaoDialog()));
    vImportLayout->addSpacing(20);
    vImportLayout->addWidget(verBtn, 0, Qt::AlignLeft);
    vImportLayout->addLayout(hboxImport);

    /*
     * Layout para inserir do teclado
     */
    insertDataBtn = new QPushButton(tr("Inserir dados"), this);
    insertDataBtn->setFixedWidth(verBtn->width());
    connect(insertDataBtn, SIGNAL(clicked()), this, SLOT(insertExperimentalData()));
    vInsertLayout->addWidget(insertDataBtn);

    vGlobalLayout->addLayout(vImportLayout);
    vGlobalLayout->addLayout(vInsertLayout);
    groupDados->setLayout(vGlobalLayout);

    changeRadio();


    /*
     * Spin Box do número de curvas
     */
    nrCurvaSpin = new QSpinBox(this);
    nrCurvaSpin->setRange(1, 3);
    nrCurvaSpin->setSingleStep(1);
    nrCurvaSpin->setValue(1);
    nrCurvaSpin->setFixedWidth(50);

    /* Spin Box do grau do polinomio */
    grauPolinSpin = new QSpinBox(this);
    grauPolinSpin->setRange(1, 6);
    grauPolinSpin->setSingleStep(1);
    grauPolinSpin->setValue(1);
    grauPolinSpin->setFixedWidth(50);

    vbox->addWidget(label1);
    vbox->addWidget(nrCurvaSpin);
    vbox->addWidget(label2);
    vbox->addWidget(grauPolinSpin);
    vbox->addWidget(label3);
    vbox->addSpacing(10);
    vbox->addWidget(groupDados);

    setLayout(vbox);
}

ConfigInitialPage::~ConfigInitialPage() {}

void ConfigInitialPage::changeRadio()
{
    if (importRadio->isChecked())
    {
        insertDataBtn->setVisible(false);
        verBtn->setVisible(true);
        openFileBtn->setVisible(true);
    }
    else if (insertRadio->isChecked()) {
        insertDataBtn->setVisible(true);
        verBtn->setVisible(false);
        openFileBtn->setVisible(false);
    }
}

void ConfigInitialPage::verFormatacaoDialog()
{
    QDialog* verDialog = new QDialog(this);
    verDialog->setWindowTitle(tr("Formatação do Arquivo de Entrada"));
    QVBoxLayout* vbox = new QVBoxLayout;

    QLabel* labelTitle = new QLabel(tr("<b>Formatação</b>"), this);
    labelTitle->setAlignment(Qt::AlignCenter);

    QLabel* textLbl = new QLabel(
            tr("Como você pode ver abaixo, o <b>#1</b> indica a primeira curva a ser plotada. ")
            + tr("Na coluna da esquerda são os valores da variável <b>x</b> (variável independente) e ")
            + tr("na coluna direita os valores da variável <b>y</b> (variável dependente).\n")
            + tr("Os valores de x e y podem ser separados por TAB ou SPACE como pode ser observado ")
            + tr("na \"Curva 1\" e na \"Curva 2\", respectivamente."),
    this);
    textLbl->setWordWrap(true);
    QLabel* verFormatacaoImageLabel = new QLabel(this);
    verFormatacaoImageLabel->setPixmap(QPixmap(":/images/logo/verformatacao.png"));
    QPushButton* okBtn = new QPushButton(tr("OK"), this);
    okBtn->setFixedWidth(50);
    connect(okBtn, SIGNAL(clicked()), verDialog, SLOT(close()));

    vbox->addWidget(labelTitle);
    vbox->addSpacing(5);
    vbox->addWidget(textLbl);
    vbox->addSpacing(5);
    vbox->addWidget(verFormatacaoImageLabel);
    vbox->addWidget(okBtn, 0, Qt::AlignCenter);
    verDialog->setLayout(vbox);    
    verDialog->show();
}

void ConfigInitialPage::openFileForImport()
{
    importFileName = QFileDialog::getOpenFileName(this, tr("Escolha um arquivo"));
    if (importFileName.isEmpty())
        return;

    importFile = new QFile(importFileName);
    if (!importFile->open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("Erro ao abrir o arquivo"), tr("Não foi possivel abrir o arquivo!"));
        return;
    }

    QTextStream stream(importFile);

    QString strFile = stream.readAll();
    parseImportFile(strFile);

}

bool ConfigInitialPage::parseImportFile(const QString &content)
{
    QString formatedStr = content;

    QRegExp expCurve("/#([\\d])/");
    QStringList curvesStr = formatedStr.split("#");

    _parseImportFile(curvesStr);

    return true;
}

bool ConfigInitialPage::_parseImportFile(const QStringList &points)
{
    bool syntax = true;
    foreach (QString pointsStr, points)
    {
        syntax = _getPoints(pointsStr);
        if (!syntax)
            return false;
    }

    return true;
}

bool ConfigInitialPage::_getPoints(const QString &content)
{
    QString pointStr = QString(content);

    QStringList lines = pointStr.split("\n");
    lines.removeAt(0);

    QRegExp regexp("([\\-\\d\\.]+)[\\s\\t]+([\\-\\d\\.]+).*");
    std::vector<Point> points;
    for (int i = 0; i < lines.size(); i++)
    {
        if (regexp.exactMatch(lines.at(i)))
        {
            Point p(regexp.cap(1).toDouble(), regexp.cap(2).toDouble());
            points.push_back(p);
        }
    }

    Curve curve;
    if (points.size() > 0)
    {
        curve.addPointByArray(points);
        curves.push_back(curve);
    }

    emit completeChanged();
    return true;
}

void ConfigInitialPage::insertExperimentalData()
{
    dialogInsertData = new QDialog(this);

    QVBoxLayout* vbox = new QVBoxLayout;
    QHBoxLayout* hTablesLayout = new QHBoxLayout;

    dialogInsertData->setWindowTitle(tr("Insira os pontos experimentais"));

    QStringList horizHeader;
    horizHeader << tr("x") << tr("y");

    bool jafoi = false;
    int tblSize = 0;

    if (tableWidgets.size() > 0)
    {
        jafoi = true;
        tblSize = tableWidgets.size();
        if (nrCurvaSpin->value() < tblSize)
        {
            tableWidgets.erase(tableWidgets.begin()+nrCurvaSpin->value(), tableWidgets.end());
            tblSize = tableWidgets.size();
        }
    }

    for (int i = 0; i < nrCurvaSpin->value(); i++)
    {
        QLabel *label = new QLabel(tr("Curva %1").arg(i+1), dialogInsertData);
        QVBoxLayout* vBoxCurva = new QVBoxLayout;
        vBoxCurva->addWidget(label, 0, Qt::AlignCenter);

        if (jafoi && tblSize > i)
        {
            vBoxCurva->addWidget(tableWidgets[i], 0, Qt::AlignCenter);

            hTablesLayout->addLayout(vBoxCurva);
            continue;
        }

        QTableWidget* tableWidget = new QTableWidget(dialogInsertData);
        tableWidget->setRowCount(15);
        tableWidget->setColumnCount(2);

        tableWidget->setHorizontalHeaderLabels(horizHeader);
        tableWidget->setFixedHeight(400);

        connect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(currentItemTableChanged(QTableWidgetItem*)));

        vBoxCurva->addWidget(tableWidget, 0, Qt::AlignCenter);

        hTablesLayout->addLayout(vBoxCurva);
        tableWidgets.push_back(tableWidget);
    }

    vbox->addLayout(hTablesLayout);
    QPushButton* addRowBtn = new QPushButton(tr("+"), this);
    addRowBtn->setFixedWidth(50);
    connect(addRowBtn, SIGNAL(clicked()), this, SLOT(addRowInTable()));
    vbox->addWidget(addRowBtn, 0, Qt::AlignLeft);

    QLabel* labelUnit = new QLabel(tr("Unidades de Medidas"), dialogInsertData);
    vbox->addWidget(labelUnit, 0, Qt::AlignCenter);
    QLabel* labelX = new QLabel(tr("x: "), dialogInsertData);
    labelX->setFixedWidth(20);
    unitXEdit = new QLineEdit(tr("cm"), dialogInsertData);
    unitXEdit->setFixedWidth(70);

    int spacing = 80 * nrCurvaSpin->value();

    QHBoxLayout* hUnitLay1 = new QHBoxLayout;

//    hUnitLay1->addSpacing(spacing);
    hUnitLay1->addWidget(labelX, 0, Qt::AlignLeft);
    hUnitLay1->addWidget(unitXEdit, 0, Qt::AlignLeft);
    hUnitLay1->addSpacing(spacing);
    
    QLabel* labelY = new QLabel(tr("y: "), dialogInsertData);
    labelY->setFixedWidth(20);
    unitYEdit = new QLineEdit(tr("cm"), dialogInsertData);
    unitYEdit->setFixedWidth(70);

    hUnitLay1->addWidget(labelY, 5, Qt::AlignRight);
    hUnitLay1->addWidget(unitYEdit, 5, Qt::AlignRight);
//    hUnitLay1->addSpacing(spacing);
    
    vbox->addLayout(hUnitLay1);

    QHBoxLayout* hButtonsLay = new QHBoxLayout;
    QPushButton* okBtn = new QPushButton(tr("OK"), dialogInsertData);
    okBtn->setFixedWidth(80);
    QPushButton* cancelBtn = new QPushButton(tr("Cancelar"), dialogInsertData);
    cancelBtn->setFixedWidth(80);
    connect(okBtn, SIGNAL(clicked()), this, SLOT(okThenGetExperimentalPoints()));
    connect(cancelBtn, SIGNAL(clicked()), dialogInsertData, SLOT(close()));

    hButtonsLay->addWidget(cancelBtn, 0, Qt::AlignRight);
    hButtonsLay->addWidget(okBtn, 0, Qt::AlignLeft);

    vbox->addSpacing(20);
    vbox->addLayout(hButtonsLay);
    dialogInsertData->setLayout(vbox);
    dialogInsertData->show();

    return;
}

void ConfigInitialPage::currentItemTableChanged(QTableWidgetItem *item)
{
    QString itemStr = item->text();
    int countVirg = 0;
    int countPoint = 0;
    int countPlus = 0;
    int countMinus = 0;

    int temp1 = 0;
    int temp2 = 0;
    int temp3 = 0;
    int temp4 = 0;
    for (int i = 0; i < itemStr.length(); i++)
        if (itemStr.at(i) == QChar(','))
            countVirg++;
        else
        if (itemStr.at(i) == QChar('.'))
            countPoint++;
        else
        if (itemStr.at(i) == QChar('-'))
            countMinus++;
        else
        if (itemStr.at(i) == QChar('+'))
            countPlus++;

    for (int i = 0; i < itemStr.length(); i++)
        if (itemStr.at(i) == QChar(','))
        {
            temp1++;
            if (temp1 < countVirg)
                itemStr.remove(i, 1);
        } else
        if (itemStr.at(i) == QChar('.'))
        {
            temp2++;
            if (temp2 < countPoint)
                itemStr.remove(i, 1);
        } else
        if (itemStr.at(i) == QChar('+'))
        {
            temp3++;
            if (temp3 < countPlus)
                itemStr.remove(i, 1);
        } else
        if (itemStr.at(i) == QChar('-'))
        {
            temp4++;
            if (temp4 < countMinus)
                itemStr.remove(i, 1);
        }

    itemStr.replace(QChar(','), QChar('.'));
    itemStr.replace(QString("+"), QString(""));
    itemStr.replace(QRegExp(QString("[^0-9\\.\\-]+")), QString(""));

    item->setText(itemStr);
}

void ConfigInitialPage::addRowInTable()
{
    for (unsigned int i = 0; i < tableWidgets.size(); i++)
        tableWidgets.at(i)->setRowCount(tableWidgets.at(i)->rowCount()+1);
}

void ConfigInitialPage::okThenGetExperimentalPoints()
{
    grauPolin = grauPolinSpin->value();
    nrCurves = nrCurvaSpin->value();
    curves.clear();

    for (unsigned int i = 0; i < tableWidgets.size(); i++)
    {
        std::vector<Point> points;

        for (int j = 0; j < tableWidgets.at(i)->rowCount(); j++)
        {
            QTableWidgetItem* xItem = tableWidgets.at(i)->item(j, 0);
            QTableWidgetItem* yItem = tableWidgets.at(i)->item(j, 1);

            if ((xItem == 0x0 && !(yItem == 0x0)) || (!(xItem == 0x0) && yItem == 0x0))
            {
                QString val;
                if (xItem)
                {
                    val = xItem->text();
                    if (!val.isEmpty())
                        return _atentionXYValues();
                    else
                        continue;
                }

                if (yItem)
                {
                    val = yItem->text();
                    if (!val.isEmpty())
                        return _atentionXYValues();
                    else
                        continue;
                }
            }
            if (xItem == 0x0 && yItem == 0x0)
                break;

            QString xStr = QString(xItem->text());
            QString yStr = QString(yItem->text());

            if ((xStr.isEmpty() && !yStr.isEmpty()) || (!xStr.isEmpty() && yStr.isEmpty()))
                return _atentionXYValues();

            if (xStr.isEmpty() && yStr.isEmpty())
                break;

            double x = xStr.toDouble();
            double y = yStr.toDouble();

            points.push_back(Point(x, y));
        }

        if (!points.empty())
        {
            Curve c;
            c.addPointByArray(points);
            curves.push_back(c);
        }
    }

    dialogInsertData->close();
    emit completeChanged();
    return;
}

void ConfigInitialPage::_atentionXYValues()
{
    QMessageBox::warning(this, tr("Atenção"), tr("Para cada ponto, deve-se inserir os valores de x e y"));
}

bool ConfigInitialPage::isComplete() const
{
    return !curves.empty();
}

int ConfigInitialPage::getGrauPolin() const
{
    if (grauPolinSpin->value() > 0)
        return grauPolinSpin->value();
    else
        return 0;
}
