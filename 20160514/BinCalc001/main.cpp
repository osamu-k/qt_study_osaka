#include "bincalcwidget.h"
#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont f = a.font();
    f.setPointSize( 32 );
    a.setFont( f );

    BinCalcWidget w;
    w.show();

    return a.exec();
}
