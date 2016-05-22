#ifndef CELL_H
#define CELL_H

#include <QWidget>
#include <QHBoxLayout>
#include "piece.h"

class Cell : public QWidget
{
    Q_OBJECT
public:
    explicit Cell( int row, int column, QWidget *parent = 0);

    void setPiece( Piece *p );

    Piece *piece() const
    {
        return m_piece;
    }

signals:
    void clicked( int row, int column );

public slots:

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    int m_row;
    int m_column;
    QHBoxLayout *m_layout;
    Piece *m_piece;
};

#endif // CELL_H
