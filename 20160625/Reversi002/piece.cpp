#include "piece.h"

#include <QPainter>

Piece::Piece(QWidget *parent)
    : QWidget(parent)
    , m_side( UnknownSide )
{

}

void Piece::paintEvent(QPaintEvent *)
{
    QPainter painter( this );

    painter.setRenderHint( QPainter::Antialiasing );

    if( m_side == DarkSide ){
        painter.setBrush( Qt::black );
    }
    else if( m_side == LightSide ){
        painter.setBrush( Qt::white );
    }
    else{
        return;
    }
    painter.setPen( Qt::black );

    painter.drawEllipse( rect().adjusted(1,1,-2,-2) );
}

void Piece::reverse()
{
    if( m_side == LightSide ){
        m_side = DarkSide;
    }
    else if( m_side == DarkSide ){
        m_side = LightSide;
    }
    update();
}
