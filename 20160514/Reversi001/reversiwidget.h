#ifndef REVERSIWIDGET_H
#define REVERSIWIDGET_H

#include <QWidget>
#include <QVector>

#include "cell.h"

class ReversiWidget : public QWidget
{
    Q_OBJECT

public:
    ReversiWidget(QWidget *parent = 0);
    ~ReversiWidget();

private slots:
    void cellClicked( int, int );

private:
    QVector< QVector< Cell *> > m_cells;
};

#endif // REVERSIWIDGET_H
