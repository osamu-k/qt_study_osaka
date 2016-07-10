#include "reversiwidget.h"
#include "cell.h"
#include "piece.h"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDebug>

ReversiWidget::ReversiWidget( int rowCount, int columnCount, QWidget *parent)
    : QWidget(parent)
    , m_rowCount( rowCount )
    , m_columnCount( columnCount )
    , m_frameLight( nullptr )
    , m_frameDark( nullptr )
    , m_lcdLight( nullptr )
    , m_lcdDark( nullptr )
    , m_message( nullptr )
    , m_buttonStart( nullptr )
    , m_buttonPass( nullptr )
    , m_buttonClear( nullptr )
    , m_player( PlayerNone )
    , m_pointLight( 0 )
    , m_pointDark( 0 )
{
    setAutoFillBackground( true );
    setPalette( Qt::blue );

    QWidget *header = createHeader();
    QWidget *board = createBoard();
    QWidget *footer = createFooter();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget( header, 0 );
    layout->addWidget( board, 1 );
    layout->addWidget( footer, 0 );

    setLayout( layout );

    board->setMinimumSize( 500, 500 );

    connect( m_buttonStart, SIGNAL(clicked(bool)),
             this, SLOT(start()) );
    connect( m_buttonPass, SIGNAL(clicked(bool)),
             this, SLOT(pass()) );
    connect( m_buttonClear, SIGNAL(clicked(bool)),
             this, SLOT(clear()) );

    setPlayer( PlayerNone );

//    int row = m_rowCount/2 - 1;
//    int column = m_columnCount/2 - 1;

//    Piece *p = new Piece;
//    p->setSide( Piece::LightSide );

//    m_cells[row][column]->setPiece( p );

//    p = new Piece;
//    p->setSide( Piece::DarkSide );
//    m_cells[row][column+1]->setPiece( p );


//    p = new Piece;
//    p->setSide( Piece::DarkSide );
//    m_cells[row+1][column]->setPiece( p );

//    p = new Piece;
//    p->setSide( Piece::LightSide );
//    m_cells[row+1][column+1]->setPiece( p );
}

ReversiWidget::~ReversiWidget()
{

}

QWidget *ReversiWidget::createHeader()
{
    QWidget *widget = new QWidget;

    m_frameLight = new QFrame;
    m_frameLight->setAutoFillBackground( true );
    m_frameLight->setPalette( Qt::cyan );
    m_frameLight->setFrameStyle( QFrame::Panel | QFrame::Raised );
    m_frameLight->setLineWidth( 2 );

    {
        Piece *piece = new Piece;
        piece->setSide( Piece::LightSide );
        piece->setMinimumSize( 30, 30 );

        m_lcdLight = new QLCDNumber;
        m_lcdLight->setDigitCount( 2 );
        m_lcdLight->display( 0 );

        QHBoxLayout *layoutLight = new QHBoxLayout;
        layoutLight->addWidget( piece );
        layoutLight->addWidget( m_lcdLight );

        m_frameLight->setLayout( layoutLight );
    }

    m_message = new QLineEdit;
    m_message->setReadOnly( true );
    m_message->setFocusPolicy( Qt::NoFocus );

    m_frameDark = new QFrame;
    m_frameDark->setAutoFillBackground( true );
    m_frameDark->setPalette( Qt::cyan );
    m_frameDark->setFrameStyle( QFrame::Panel | QFrame::Raised );
    m_frameDark->setLineWidth( 2 );
    {
        Piece *piece = new Piece;
        piece->setSide( Piece::DarkSide );
        piece->setMinimumSize( 30, 30 );

        m_lcdDark = new QLCDNumber;
        m_lcdDark->setDigitCount( 2 );
        m_lcdDark->display( 0 );

        QHBoxLayout *layoutDark = new QHBoxLayout;
        layoutDark->addWidget( m_lcdDark );
        layoutDark->addWidget( piece );

        m_frameDark->setLayout( layoutDark );
    }

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget( m_frameLight );
    layout->addWidget( m_message, 1 );
    layout->addWidget( m_frameDark );

    widget->setLayout( layout );

    return widget;
}

QWidget *ReversiWidget::createBoard()
{
    QWidget *widget = new QWidget;

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setMargin( 0 );
    gridLayout->setSpacing( 0 );

    m_cells.resize( m_rowCount );
    for( int row = 0; row < m_rowCount; row++ ){
        m_cells[ row ].resize( m_columnCount );
        for( int column = 0; column < m_columnCount; column++ ){
            Cell *cell = new Cell( row, column );
            gridLayout->addWidget( cell, row, column );
            connect( cell, SIGNAL(clicked(int,int)),
                     this, SLOT(cellClicked(int,int)) );
            m_cells[row][column] = cell;
        }
    }

    widget->setLayout( gridLayout );

    return widget;
}

/*
 *
 *
 *
 *
 *
 *
 *
 */

QWidget *ReversiWidget::createFooter()
{
    QWidget *widget = new QWidget;

    m_buttonStart = new QPushButton( tr("Start") );
    m_buttonPass  = new QPushButton( tr("Pass") );
    m_buttonClear = new QPushButton( tr("Clear") );

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget( m_buttonStart );
    layout->addWidget( m_buttonPass );
    layout->addWidget( m_buttonClear );

    widget->setLayout( layout );

    return widget;
}

void ReversiWidget::start()
{
    qDebug() << "start !";

    int row = m_rowCount/2 - 1;
    int column = m_columnCount/2 - 1;

    Piece *p = new Piece;
    p->setSide( Piece::LightSide );

    m_cells[row][column]->setPiece( p );

    p = new Piece;
    p->setSide( Piece::DarkSide );
    m_cells[row][column+1]->setPiece( p );

    p = new Piece;
    p->setSide( Piece::DarkSide );
    m_cells[row+1][column]->setPiece( p );

    p = new Piece;
    p->setSide( Piece::LightSide );
    m_cells[row+1][column+1]->setPiece( p );

    updatePoints();

    setPlayer( PlayerLight );
}

void ReversiWidget::pass()
{
    qDebug() << "pass !";

    switch( m_player ){
    case PlayerLight:
        setPlayer( PlayerDark );
        break;
    case PlayerDark:
        setPlayer( PlayerLight );
        break;
    default:
        break;
    }
}

void ReversiWidget::clear()
{
    qDebug() << "clear !";

    for( int row = 0; row < m_rowCount; row++ ){
        for( int column = 0; column < m_columnCount; column++ ){
            m_cells[row][column]->setPiece( nullptr );
        }
    }

    updatePoints();

//    foreach( QVector<Cell *> row, m_cells ){
//        foreach( Cell *cell, row ){
//            cell->setPiece( nullptr );
//        }
//    }

//    for( QVector<Cell *> &row : m_cells ){
//        for( Cell *cell : row ){
//            cell->setPiece( nullptr );
//        }
//    }

    setPlayer( PlayerNone );
}

void ReversiWidget::setPlayer( Player player )
{
    m_player = player;

    switch( m_player ){
    case PlayerNone:
        m_frameLight->setPalette( Qt::cyan );
        m_frameDark->setPalette( Qt::cyan );
        m_message->setText( tr("Click start button.") );
        break;
    case PlayerLight:
        m_frameLight->setPalette( Qt::yellow );
        m_frameDark->setPalette( Qt::cyan );
        m_message->setText( tr("Light's turn.") );
        break;
    case PlayerDark:
        m_frameLight->setPalette( Qt::cyan );
        m_frameDark->setPalette( Qt::yellow );
        m_message->setText( tr("Dark's turn.") );
        break;
    default:
        break;
    }
}

void ReversiWidget::cellClicked(int row, int column)
{
    qDebug() << "ReversiWidget::cellClicked(" << row << "," << column << ") called !";

//    Piece *p = m_cells[row][column]->piece();
//    if( p ){
//        p->reverse();
//    }

    Piece *piece = nullptr;
    Player nextPlayer = PlayerNone;

    switch( m_player ){
    case PlayerLight:
        piece = new Piece;
        piece->setSide( Piece::LightSide );
        nextPlayer = PlayerDark;
        break;
    case PlayerDark:
        piece = new Piece;
        piece->setSide( Piece::DarkSide );
        nextPlayer = PlayerLight;
        break;
    default:
        break;
    }

    if( piece != nullptr ){
        m_cells[row][column]->setPiece( piece );
        setPlayer( nextPlayer );
    }

    updatePoints();
}

void ReversiWidget::updatePoints()
{
    m_pointLight = 0;
    m_pointDark = 0;

    for( int row = 0; row < m_rowCount; row++ ){
        for( int column = 0; column < m_columnCount; column++ ){
            Piece *piece = m_cells[row][column]->piece();
            if( piece != nullptr ){
                switch( piece->side() ){
                case Piece::LightSide:
                    m_pointLight ++;
                    break;
                case Piece::DarkSide:
                    m_pointDark ++;
                    break;
                default:
                    break;
                }
            }
        }
    }

    m_lcdLight->display( m_pointLight );
    m_lcdDark->display( m_pointDark );
}
