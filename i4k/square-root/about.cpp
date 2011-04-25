#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent)
    : QDialog(parent)
    , aboutUi(new Ui::About)
{
    aboutUi->setupUi(this);
    connect(aboutUi->okBtn, SIGNAL(clicked()), this, SLOT(close()));
}

About::~About()
{
    delete aboutUi;
}
