#include "game.h"

Game::Game( int rowCount, int columnCount, QObject *parent )
    : QObject(parent)
    , m_rowCount( rowCount )
    , m_columnCount( columnCount )
{
    m_cells.resize( m_rowCount );
    for( int row = 0; row < m_rowCount; row++ ){
        m_cells[ row ].resize( m_columnCount );
        for( int column = 0; column < m_columnCount; column++ ){
            m_cells[row][column] = PlayerNone;
        }
    }
}

int Game::rowCount() const
{
    return m_rowCount;
}

int Game::columnCount() const
{
    return m_columnCount;
}

int Game::pointLight() const
{
    return m_pointLight;
}

int Game::pointDark() const
{
    return m_pointDark;
}

Player Game::currentPlayer() const
{
    return m_currentPlayer;
}

void Game::start()
{
    int row = m_rowCount/2 - 1;
    int column = m_columnCount/2 - 1;

    setOneCell( row, column, PlayerLight );
    setOneCell( row+1, column+1, PlayerLight );
    setOneCell( row+1, column, PlayerDark );
    setOneCell( row, column+1, PlayerDark );

    setCurrentPlayer( PlayerLight );
    m_passCount = 0;
    updatePoints();
    m_gameOver = false;
}

void Game::pass()
{
    switch( m_currentPlayer ){
    case PlayerLight:
        setCurrentPlayer( PlayerDark );
        break;
    case PlayerDark:
        setCurrentPlayer( PlayerLight );
        break;
    default:
        break;
    }

    m_passCount++;

    checkGameOver();
}

void Game::clear()
{
    for( int row = 0; row < m_rowCount; row++ ){
        for( int column = 0; column < m_columnCount; column++ ){
            setOneCell( row, column, PlayerNone );
        }
    }

    setCurrentPlayer( PlayerNone );
    m_passCount = 0;
    updatePoints();
    m_gameOver = false;
}

void Game::setCellPlayer( int row, int column, Player player )
{
    if( m_gameOver )
        return;

    Player nextPlayer = PlayerNone;

    switch( m_currentPlayer ){
    case PlayerLight:
        nextPlayer = PlayerDark;
        break;
    case PlayerDark:
        nextPlayer = PlayerLight;
        break;
    default:
        return;
    }

    QList<CellPosition> reversibleCells;

    checkReversibleCells( row, column, player, reversibleCells );
    if( reversibleCells.size() == 0 )
        return;

    setOneCell( row, column, player );
    for( CellPosition pos : reversibleCells ){
        setOneCell( pos.row, pos.column, player );
    }

    setCurrentPlayer( nextPlayer );
    m_passCount = 0;
    updatePoints();

    checkGameOver();
}

void Game::setOneCell(int row, int column, Player player)
{
    m_cells[row][column] = player;
    emit cellChanged( row, column, player );
}

void Game::setCurrentPlayer( Player player )
{
    m_currentPlayer = player;
    emit playerChanged( player );
}

void Game::updatePoints()
{
    m_pointLight = 0;
    m_pointDark = 0;

    for( QVector<Player> &row : m_cells ){
        for( Player player: row ){
            switch( player ){
            case PlayerLight:
                m_pointLight++;
                break;
            case PlayerDark:
                m_pointDark++;
                break;
            default:
                break;
            }
        }
    }
    emit pointChanged( m_pointLight, m_pointDark );
}

void Game::checkReversibleCells(
        int row, int column, Player player,
        QList<CellPosition> &reversibleCells )
{
    if( m_cells[row][column] != PlayerNone )
        return;

    checkReversibleOneDirection( row, column, player, -1, -1, reversibleCells );
    checkReversibleOneDirection( row, column, player,  0, -1, reversibleCells );
    checkReversibleOneDirection( row, column, player, +1, -1, reversibleCells );
    checkReversibleOneDirection( row, column, player, +1,  0, reversibleCells );
    checkReversibleOneDirection( row, column, player, +1, +1, reversibleCells );
    checkReversibleOneDirection( row, column, player,  0, +1, reversibleCells );
    checkReversibleOneDirection( row, column, player, -1, +1, reversibleCells );
    checkReversibleOneDirection( row, column, player, -1,  0, reversibleCells );
}

void Game::checkReversibleOneDirection(
        int row, int column, Player player,
        int rowDirection, int columnDirection,
        QList<CellPosition> &reversibleCells )
{
    QList<CellPosition> cells;

    while( true ){
        row += rowDirection;
        column += columnDirection;
        if( row < 0 )
            break;
        if( row >= m_rowCount )
            break;
        if( column < 0 )
            break;
        if( column >= m_columnCount )
            break;

        if( m_cells[row][column] == PlayerNone )
            break;

        if( m_cells[row][column] == player ){
            reversibleCells << cells;
            break;
        }
        cells << CellPosition( row, column );
    }
}

void Game::checkGameOver()
{
    m_gameOver = false;

    if( (m_pointLight + m_pointDark) == (m_rowCount * m_columnCount) ){
        m_gameOver = true;
    }
    else if( m_pointLight == 0 ){
        m_gameOver = true;
    }
    else if( m_pointDark == 0 ){
        m_gameOver = true;
    }
    else if( m_passCount == 2 ){
        m_gameOver = true;
    }

    if( m_gameOver ){
        Player winner = PlayerNone;
        if( m_pointLight > m_pointDark ){
            winner = PlayerLight;
        }
        else if( m_pointLight < m_pointDark ){
            winner = PlayerDark;
        }
        emit gameOver( winner );
    }
}
