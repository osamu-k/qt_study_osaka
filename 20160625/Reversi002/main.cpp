#include "reversiwidget.h"
#include <QApplication>
#include <QFont>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    QLocale::Language language = QLocale::system().language();
    if( language == QLocale::Japanese ){
        translator.load( QString(":/Reversi001_ja") );
        a.installTranslator( &translator );
    }

    QFont afont = a.font();
    afont.setPointSize( 18 );
    a.setFont( afont );

    ReversiWidget w( 8, 8 );
    w.show();

    return a.exec();
}
