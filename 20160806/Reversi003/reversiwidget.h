#ifndef REVERSIWIDGET_H
#define REVERSIWIDGET_H

#include <QFrame>
#include <QLCDNumber>
#include <QLineEdit>
#include <QList>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include <QVector>

#include "game.h"
#include "cell.h"

class ReversiWidget : public QWidget
{
    Q_OBJECT

public:
    ReversiWidget( Game *game, Player player, QWidget *parent = 0);
    ~ReversiWidget();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void start();
    void pass();
    void clear();

    void cellClicked( int, int );

    void cellChanged( int row, int column, Player player );
    void pointChanged( int pointLight, int pointDark );
    void playerChanged( Player player );
    void gameOver( Player );

    void messageBoxFinished();

private:
    QWidget *createHeader();
    QWidget *createBoard();
    QWidget *createFooter();

    void setCurrentPlayer( Player player );
    void updatePoints();

    void checkReversibleCells(
            int row, int column, Piece::Side side,
            QList<Cell *> &reversibleCells );

    void checkReversibleOneDirection(
            int row, int column, Piece::Side side,
            int rowDirection, int columnDirection,
            QList<Cell *> &reversibleCells );

    void checkGameOver();

    Game *m_game;
    Player m_player;
    int m_rowCount;
    int m_columnCount;
    QVector< QVector< Cell *> > m_cells;

    QFrame *m_frameLight;
    QFrame *m_frameDark;
    QLCDNumber *m_lcdLight;
    QLCDNumber *m_lcdDark;
    QLineEdit *m_message;

    QPushButton *m_buttonStart;
    QPushButton *m_buttonPass;
    QPushButton *m_buttonClear;

    QMessageBox *m_messageBox;
};

#endif // REVERSIWIDGET_H
