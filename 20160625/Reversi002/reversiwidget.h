#ifndef REVERSIWIDGET_H
#define REVERSIWIDGET_H

#include <QFrame>
#include <QLCDNumber>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QVector>

#include "cell.h"

class ReversiWidget : public QWidget
{
    Q_OBJECT

public:
    ReversiWidget( int rowCount, int columnCount, QWidget *parent = 0);
    ~ReversiWidget();

private slots:
    void start();
    void pass();
    void clear();
    void cellClicked( int, int );

private:
    enum Player{
        PlayerNone,
        PlayerLight,
        PlayerDark
    };

    QWidget *createHeader();
    QWidget *createBoard();
    QWidget *createFooter();

    void setPlayer( Player player );
    void updatePoints();

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

    Player m_player;

    int m_pointLight;
    int m_pointDark;
};

#endif // REVERSIWIDGET_H
