#ifndef SESSION_H
#define SESSION_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QPixmap>
#include <QList>
#include <QTime>

class Session : public QObject
{
    Q_OBJECT
public:

    explicit Session(QString m_host,QString m_id="",QString m_pass="");
    bool preLogin();
    bool login2();
    bool login1();
    QPixmap* getCheckCode();
    QList<QStringList> query(QString years,QString term);
    QString getError(){return m_error;}

signals:

public slots:
    void setCheckCode(QString code);

private:
    QString m_host,m_id,m_pass,m_checkCode,m_error;
    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkRequest request;
    QNetworkReply *pReply;
    QString m_tagCode;
    QString m_viewState;
//    QString getViewState(QString html);
    QString getArgu(QString argu, QString html);
    QByteArray encodeURI(QString str);
    QString getName(QString html);
    QList<QStringList> getScore(QString html);
    QStringList getInputName(QString url);


};

#endif // SESSION_H
