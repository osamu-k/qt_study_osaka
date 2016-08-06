#include "reversiwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QLocale>
#include <QScreen>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    QLocale::Language language = QLocale::system().language();
    if( language == QLocale::Japanese ){
        translator.load( QString(":/Reversi003") + "_ja" );
        a.installTranslator( &translator );
    }

    QFont myFont = a.font();
    myFont.setPointSize( 18 );
    a.setFont( myFont );

    Game game( 8, 8 );
    ReversiWidget w1( &game, PlayerLight );
    ReversiWidget w2( &game, PlayerDark );

    w1.show();
    w2.show();

    QSize screenSize = a.desktop()->size();
    QSize frameSize1 = w1.frameSize();
    QSize frameSize2 = w2.frameSize();
    w1.move( (screenSize.width() - (frameSize1.width() + frameSize2.width())) / 2,
             (screenSize.height() - frameSize1.height()) / 2 );
    w2.move( w1.pos().x() + frameSize1.width(), w1.pos().y() );

    return a.exec();
}
