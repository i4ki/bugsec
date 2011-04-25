/********************************************************************************
** Form generated from reading UI file 'configpage.ui'
**
** Created: Sat Feb 13 15:48:29 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGPAGE_H
#define UI_CONFIGPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_WizardPage
{
public:

    void setupUi(QWizardPage *WizardPage)
    {
        if (WizardPage->objectName().isEmpty())
            WizardPage->setObjectName(QString::fromUtf8("WizardPage"));
        WizardPage->resize(400, 300);

        retranslateUi(WizardPage);

        QMetaObject::connectSlotsByName(WizardPage);
    } // setupUi

    void retranslateUi(QWizardPage *WizardPage)
    {
        WizardPage->setWindowTitle(QApplication::translate("WizardPage", "WizardPage", 0, QApplication::UnicodeUTF8));
        WizardPage->setTitle(QApplication::translate("WizardPage", "Configura\303\247\303\243o Inicial", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WizardPage: public Ui_WizardPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGPAGE_H
