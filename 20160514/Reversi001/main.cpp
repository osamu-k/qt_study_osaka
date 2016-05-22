#include "reversiwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReversiWidget w;
    w.show();

    return a.exec();
}
