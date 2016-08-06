#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QVector>

enum Player {
    PlayerNone,
    PlayerLight,
    PlayerDark
};

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game( int rowCount, int columnCount, QObject *parent = 0);

    int rowCount() const;
    int columnCount() const;
    int pointLight() const;
    int pointDark() const;
    Player currentPlayer() const;

signals:
    void cellChanged( int row, int column, Player player );
    void pointChanged( int pointLight, int pointDark );
    void playerChanged( Player player );
    void gameOver( Player );

public slots:
    void start();
    void pass();
    void clear();
    void setCellPlayer( int row, int column, Player player );

private:
    struct CellPosition{
        CellPosition( int r, int c )
            : row(r)
            , column(c)
        {
        }

        int row;
        int column;
    };

    void setCurrentPlayer( Player player );
    void setOneCell(int row, int column, Player player);
    void updatePoints();

    void checkReversibleCells(
            int row, int column, Player player,
            QList<CellPosition> &reversibleCells );

    void checkReversibleOneDirection(
            int row, int column, Player player,
            int rowDirection, int columnDirection,
            QList<CellPosition> &reversibleCells );

    void checkGameOver();

    int m_rowCount;
    int m_columnCount;
    QVector< QVector< Player > > m_cells;

    Player m_currentPlayer;
    int m_passCount;
    int m_pointLight;
    int m_pointDark;
    bool m_gameOver;
};

#endif // GAME_H
