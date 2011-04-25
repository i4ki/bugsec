/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created: Sat Jun 5 22:19:41 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_4;
    QPushButton *okBtn;

    void setupUi(QWidget *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QString::fromUtf8("About"));
        About->resize(421, 284);
        label_5 = new QLabel(About);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(160, 170, 231, 17));
        label_6 = new QLabel(About);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(160, 190, 231, 17));
        label_2 = new QLabel(About);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(160, 30, 221, 20));
        QFont font;
        font.setPointSize(12);
        label_2->setFont(font);
        label_3 = new QLabel(About);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(160, 40, 231, 111));
        QFont font1;
        font1.setPointSize(10);
        label_3->setFont(font1);
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3->setWordWrap(true);
        label = new QLabel(About);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 101, 141));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/logo/brasao3.png")));
        label_4 = new QLabel(About);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(160, 150, 241, 17));
        label_4->setWordWrap(true);
        okBtn = new QPushButton(About);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setGeometry(QRect(290, 240, 91, 27));

        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QWidget *About)
    {
        About->setWindowTitle(QApplication::translate("About", "Form", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("About", "Orientador: Jos\303\251 Ricardo Marinelli", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("About", "Projeto: Bolsa Perman\303\252ncia", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("About", "<b>Minimos Quadrados 1.0 </b>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("About", "Este programa utiliza o m\303\251todo dos M\303\255nimos Quadrados para fazer o ajuste de curvas polinomiais de um conjunto de pontos.", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        label_4->setText(QApplication::translate("About", "Desenvolvedor: Bruno Vinicius Pasti", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("About", "&Fechar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
