#include "cell.h"
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QHBoxLayout>

Cell::Cell( int row, int column, QWidget *parent)
    : QWidget(parent)
    , m_row( row )
    , m_column( column )
    , m_piece( 0 )
{
    setAutoFillBackground( true );
    setPalette( Qt::green );

    m_layout = new QHBoxLayout;
    m_layout->setMargin( 2 );
    setLayout( m_layout );
}

void Cell::paintEvent(QPaintEvent *)
{
    qDebug() << "Cell::paintEvent called !";

    QPainter painter(this);

    painter.drawRect( rect().adjusted(0,0,-1,-1) );
}

void Cell::mousePressEvent(QMouseEvent *)
{
    qDebug() << "mouse pressed row=" << m_row << " colunm=" << m_column;
}

void Cell::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "mouse released row=" << m_row << " colunm=" << m_column;

    if( rect().contains( event->pos() ) ){
        qDebug() << "signal emitted vy Cell";
        emit clicked( m_row, m_column );
    }
}

void Cell::setPiece(Piece *p)
{
    if( m_piece != nullptr ){
        delete m_piece;
        m_piece = nullptr;
    }
    m_piece = p;
    if( p != nullptr ){
        m_layout->addWidget( p );
    }
}
