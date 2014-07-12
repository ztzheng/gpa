#include "qgpa.h"
#include <QApplication>
#include <QTextCodec>
#include <QStyleFactory>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("fusion"));
    QApplication a(argc, argv);
    a.addLibraryPath("./lib");
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));\
    QGpa w;
    w.show();
    return a.exec();
}
