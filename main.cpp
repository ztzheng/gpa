#include "classes/qgpa.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("./lib");
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QGpa w;
    w.show();
    return a.exec();
}
