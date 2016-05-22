#ifndef PIECE_H
#define PIECE_H

#include <QWidget>

class Piece : public QWidget
{
    Q_OBJECT
public:

    enum Side {
        UnknownSide,
        DarkSide,
        LightSide
    };

    explicit Piece(QWidget *parent = 0);

    void setSide( Side side )
    {
        m_side = side;
    }

    Side side() const
    {
        return m_side;
    }

    void reverse();

signals:

public slots:

protected:
    void paintEvent( QPaintEvent * );

private:
     Side m_side;
};

#endif // PIECE_H
