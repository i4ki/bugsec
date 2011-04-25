#ifndef ACTIONCURVE_H
#define ACTIONCURVE_H

#include <QAction>

class ActionCurve : public QAction
{
    Q_OBJECT

public:
    ActionCurve(const QString& title, QWidget* parent);
    int getIdx() const;
    void  setIdx(int i);

protected:
    int idx;
};

#endif // ACTIONCURVE_H
