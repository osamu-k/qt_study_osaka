#include "reversiwidget.h"
#include "cell.h"
#include "piece.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPainter>
#include <QVBoxLayout>
#include <QDebug>

ReversiWidget::ReversiWidget( Game *game, Player player, QWidget *parent)
    : QWidget(parent)
    , m_game( game )
    , m_player( player )
    , m_rowCount( game->rowCount() )
    , m_columnCount( game->columnCount() )
    , m_frameLight( nullptr )
    , m_frameDark( nullptr )
    , m_lcdLight( nullptr )
    , m_lcdDark( nullptr )
    , m_message( nullptr )
    , m_buttonStart( nullptr )
    , m_buttonPass( nullptr )
    , m_buttonClear( nullptr)
    , m_messageBox( nullptr )
{
    setAutoFillBackground( true );
    setPalette( Qt::blue );

    QWidget *header = createHeader();
    QWidget *board = createBoard();
    QWidget *footer = createFooter();

    QVBoxLayout *layout = new QVBoxLayout( this );
    layout->setMargin( 0 );
    layout->addWidget( header, 0 );
    layout->addWidget( board, 1 );
    layout->addWidget( footer, 0 );

    board->setMinimumSize( 500, 500 );

    connect( m_game, SIGNAL(cellChanged(int,int,Player)),
             this, SLOT(cellChanged(int,int,Player)) );
    connect( m_game, SIGNAL(playerChanged(Player)),
             this, SLOT(playerChanged(Player)) );
    connect( m_game, SIGNAL(pointChanged(int,int)),
             this, SLOT(pointChanged(int,int)) );
    connect( m_game, SIGNAL(gameOver(Player)),
             this, SLOT(gameOver(Player)) );

    playerChanged( PlayerNone );
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
    m_frameLight->setLineWidth(2);

    m_frameDark = new QFrame;
    m_frameDark->setAutoFillBackground( true );
    m_frameDark->setPalette( Qt::cyan );
    m_frameDark->setFrameStyle( QFrame::Panel | QFrame::Raised );
    m_frameDark->setLineWidth(2);

    m_message = new QLineEdit;
    m_message->setReadOnly( true );
    m_message->setFocusPolicy( Qt::NoFocus );

    Piece *pieceLight = new Piece;
    pieceLight->setSide( Piece::LightSide );
    pieceLight->setMinimumSize( 30, 30 );
    m_lcdLight = new QLCDNumber;
    m_lcdLight->setDigitCount( 2 );
    m_lcdLight->display( 0 );

    QHBoxLayout *layoutLight = new QHBoxLayout( m_frameLight );
    layoutLight->addWidget( pieceLight );
    layoutLight->addWidget( m_lcdLight );

    Piece *pieceDark = new Piece;
    pieceDark->setSide( Piece::DarkSide );
    pieceDark->setMinimumSize( 30, 30 );
    m_lcdDark = new QLCDNumber;
    m_lcdDark->setDigitCount( 2 );
    m_lcdDark->display( 0 );

    QHBoxLayout *layoutDark = new QHBoxLayout( m_frameDark );
    layoutDark->addWidget( m_lcdDark );
    layoutDark->addWidget( pieceDark );

    QHBoxLayout *layout = new QHBoxLayout( widget );
    layout->addWidget( m_frameLight, 0 );
    layout->addWidget( m_message, 1 );
    layout->addWidget( m_frameDark, 0 );

    return widget;
}

QWidget *ReversiWidget::createBoard()
{
    QWidget *widget = new QWidget;
    QGridLayout *gridLayout = new QGridLayout( widget );
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

    return widget;
}

QWidget *ReversiWidget::createFooter()
{
    QWidget *widget = new QWidget;

    m_buttonStart = new QPushButton( tr("Start") );
    m_buttonPass  = new QPushButton( tr("Pass") );
    m_buttonClear = new QPushButton( tr("Clear") );

    QHBoxLayout *layout = new QHBoxLayout( widget );
    layout->addWidget( m_buttonStart );
    layout->addWidget( m_buttonPass  );
    layout->addWidget( m_buttonClear );

    connect( m_buttonStart, SIGNAL(clicked(bool)), this, SLOT(start()) );
    connect( m_buttonPass , SIGNAL(clicked(bool)), this, SLOT(pass()) );
    connect( m_buttonClear, SIGNAL(clicked(bool)), this, SLOT(clear()) );

    return widget;
}

void ReversiWidget::start()
{
    qDebug() << "start !";
    m_game->start();
}

void ReversiWidget::pass()
{
    qDebug() << "pass !";
    m_game->pass();
}

void ReversiWidget::clear()
{
    qDebug() << "clear !";
    m_game->clear();
}

void ReversiWidget::cellClicked(int row, int column)
{
    qDebug() << "ReversiWidget::cellClicked(" << row << "," << column << ") called !";

    if( m_player == m_game->currentPlayer() ){
        m_game->setCellPlayer( row, column, m_player );
    }
}

void ReversiWidget::cellChanged( int row, int column, Player player )
{
    Piece *piece = nullptr;

    switch( player ){
    case PlayerLight:
        piece = new Piece;
        piece->setSide( Piece::LightSide );
        break;
    case PlayerDark:
        piece = new Piece;
        piece->setSide( Piece::DarkSide );
        break;
    default:
        break;
    }

    m_cells[row][column]->setPiece( piece );
}

void ReversiWidget::playerChanged( Player player )
{
    switch( player ){
    case PlayerNone:
        m_frameLight->setPalette( Qt::cyan );
        m_frameDark->setPalette( Qt::cyan );
        m_message->setText( tr("Click start button") );
        m_buttonStart->setEnabled( true );
        m_buttonPass->setEnabled( false );
        m_buttonClear->setEnabled( false );
        break;
    case PlayerLight:
        m_frameLight->setPalette( Qt::yellow );
        m_frameDark->setPalette( Qt::cyan );
        if( m_player == player ){
            m_message->setText( tr("Your turn !") );
        }
        else{
            m_message->setText( tr("Oppnent's turn.") );
        }
        m_buttonStart->setEnabled( false );
        m_buttonPass->setEnabled( true );
        m_buttonClear->setEnabled( true );
        break;
    case PlayerDark:
        m_frameLight->setPalette( Qt::cyan );
        m_frameDark->setPalette( Qt::yellow );
        if( m_player == player ){
            m_message->setText( tr("Your turn !") );
        }
        else{
            m_message->setText( tr("Oppnent's turn.") );
        }
        m_buttonStart->setEnabled( false );
        m_buttonPass->setEnabled( true );
        m_buttonClear->setEnabled( true );
        break;
    default:
        break;
    }
}

void ReversiWidget::pointChanged( int pointLight, int pointDark )
{
    m_lcdLight->display( pointLight );
    m_lcdDark->display( pointDark );
}

void ReversiWidget::gameOver( Player player )
{
    QString message( tr("GameOver !") );
    QString winner;

    if( player == PlayerNone ){
        winner = tr("Even, no winner.");
    }
    else if( player == m_player ){
        winner = tr("You are winner !");
    }
    else {
        winner = tr("Opponent is winner !");
    }

    message += QChar::LineFeed;
    message += winner;

    if( m_messageBox == nullptr ){
        m_messageBox = new QMessageBox( this );
        m_messageBox->setText( message );
        m_messageBox->setModal( true );
        connect( m_messageBox, SIGNAL(finished(int)),
                 this, SLOT(messageBoxFinished()) );
    }

    m_messageBox->show();

    m_frameLight->setPalette( Qt::cyan );
    m_frameDark->setPalette( Qt::cyan );
    m_buttonPass->setEnabled( false );
    m_message->setText( winner );
}

void ReversiWidget::messageBoxFinished()
{
    qDebug() << "messageBox finished.";
}

void ReversiWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if( m_player == PlayerLight ){
        painter.fillRect( rect(), Qt::white );
    }
    else if( m_player == PlayerDark ){
        painter.fillRect( rect(), Qt::black );
    }
    else{
        return;
    }
}
