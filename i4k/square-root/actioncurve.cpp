#include "actioncurve.h"

ActionCurve::ActionCurve(const QString &title, QWidget *parent)
    : QAction(title, parent)
{

}

int ActionCurve::getIdx() const
{
    return idx;
}

void ActionCurve::setIdx(int i)
{
    idx = i;
}

