#include "chesswindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    ChessWindow w;
    w.show();
    return QApplication::exec();
}
