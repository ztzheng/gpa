#ifndef LOCAL_H
#define LOCAL_H

#include <QTextCodec>
#define toLocal() toUtf8()
#define fromLocal(a) fromUtf8(a)
void initApp()
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

//        QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
//        QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
//        QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
}


#endif // LOCAL_H
