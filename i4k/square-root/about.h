#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui
{
    class About;
};

class About : public QDialog
{
    Q_OBJECT
public:
    About(QWidget* parent);
    ~About();

private:
    Ui::About *aboutUi;

};

#endif // ABOUT_H
