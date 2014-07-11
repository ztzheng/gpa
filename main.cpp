#include "qgpa.h"
#include <QApplication>
#include <QTextCodec>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("fusion"));
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));\
    QGpa w;
    w.show();
    return a.exec();
}
