#include "reversiwidget.h"
#include "cell.h"
#include "piece.h"

#include <QGridLayout>
#include <QDebug>

ReversiWidget::ReversiWidget(QWidget *parent)
    : QWidget(parent)
{
    setAutoFillBackground( true );
    setPalette( Qt::blue );

    resize( 500, 500 );

    QGridLayout *gridLayout = new QGridLayout;
//    gridLayout->setMargin( 0 );
    gridLayout->setSpacing( 0 );

    m_cells.resize( 8 );
    for( int row = 0; row < 8; row++ ){
        m_cells[ row ].resize( 8 );
        for( int column = 0; column < 8; column++ ){
            Cell *cell = new Cell( row, column );
            gridLayout->addWidget( cell, row, column );
            connect( cell, SIGNAL(clicked(int,int)),
                     this, SLOT(cellClicked(int,int)) );
            m_cells[row][column] = cell;
        }
    }

    setLayout( gridLayout );

    Piece *p = new Piece;
    p->setSide( Piece::LightSide );

    m_cells[3][3]->setPiece( p );

    p = new Piece;
    p->setSide( Piece::DarkSide );
    m_cells[3][4]->setPiece( p );


    p = new Piece;
    p->setSide( Piece::DarkSide );
    m_cells[4][3]->setPiece( p );

    p = new Piece;
    p->setSide( Piece::LightSide );
    m_cells[4][4]->setPiece( p );
}

ReversiWidget::~ReversiWidget()
{

}

void ReversiWidget::cellClicked(int row, int column)
{
    qDebug() << "ReversiWidget::cellClicked(" << row << "," << column << ") called !";

    Piece *p = m_cells[row][column]->piece();
    if( p ){
        p->reverse();
    }
}
