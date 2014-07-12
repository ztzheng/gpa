#include "session.h"
#include <QDebug>
#include <QRegExp>
#include <QUrl>
#include <QMessageBox>
#include "checkcodedlg.h"
#include <QTextCodec>

Session::Session(QString host, QString id, QString pass)
{
    m_host=host;
    m_id=id;
    m_pass=pass;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    connect(&manager,SIGNAL(finished(QNetworkReply*)),&loop,SLOT(quit()));
}

bool Session::preLogin()
{
    request.setUrl(QUrl("http://"+m_host));
    pReply=manager.get(request);
    loop.exec();
    pReply->readAll();
    QString redirect=pReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
    delete pReply;
    if(!redirect.contains("efault2")) return false;
    request.setUrl(QUrl("http://"+m_host+redirect));
    pReply=manager.get(request);
    loop.exec();
    QString html=QString::fromLocal8Bit(pReply->readAll());
    delete pReply;

    if(!html.contains(tr("用户名")))	 return false;
    m_viewState=getArgu("VIEWSTATE",html);

    if(m_viewState.isEmpty())    return false;
    m_tagCode=redirect.replace("/(","").replace(")/Default2.aspx","").replace(")/default2.aspx","");

    return true;
}

Session::ErrorType Session::createLogin()
{
    CheckCodeDlg dlg(NULL,this);
    dlg.exec();

    //获取表单name
    request.setUrl(QUrl("http://"+m_host+"/("+m_tagCode+")/default2.aspx"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    pReply=manager.get(request);
    loop.exec();
    QString html=QString::fromLocal8Bit(pReply->readAll());
    delete pReply;
    QRegExp rx("(<input name=\"\\S*\")");
    rx.indexIn(html);
    int pos=rx.indexIn(html,0);
    QString idNmae=rx.cap(1).replace("<input name=\"","").replace("\"","");
    pos=rx.indexIn(html,pos+1);
    QString passName=rx.cap(1).replace("<input name=\"","").replace("\"","");
    pos=rx.indexIn(html,pos+1);
    QString codeName=rx.cap(1).replace("<input name=\"","").replace("\"","");

//    Login
    QString eventvalidation=getArgu("EVENTVALIDATION",html);
    QByteArray data=QString("__VIEWSTATE="+m_viewState+
                            "&__EVENTVALIDATION="+eventvalidation+"&"
                            +idNmae+"="+m_id+"&"+passName+"="+m_pass+"&"+codeName+"="+m_checkCode+"&RadioButtonList1=%D1%A7%C9%FA&Button1=").toLatin1();


    pReply=manager.post(request,data);
    loop.exec();
    html=QString::fromLocal8Bit( pReply->readAll().data());
    if(html.contains(tr("验证码不正确")))        return CheckCodeError;
    if(html.contains(tr("用户名不存在")))        return NoUserError;
    if(html.contains(tr("密码错误")))        return PasswordError;
    QString redirect=pReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
    if(!redirect.contains("xs_main.aspx?xh"))	       return OtherError;
    delete pReply;
    request.setUrl(QUrl("http://"+m_host+redirect));
    pReply=manager.get(request);
    loop.exec();
    html=QString::fromLocal8Bit(pReply->readAll());  
    delete pReply;
    //获取姓名
    if(!html.contains("xhxm")) return OtherError;
    m_name=getName(html);
    return NoError;
}

void Session::setCheckCode(QString code)
{
    m_checkCode=code;
}

//QString Session::getViewState(QString html)
//{
//    QRegExp rx("(VIEWSTATE\"\\s*value=\"\\S*\"\\s*/>)");
//    rx.indexIn(html);
//    QString tmp=rx.cap(1).replace("VIEWSTATE\" value=\"","").replace("\" />","");
//    return encodeURI(tmp);
//}

QString Session::getArgu(QString argu,QString html)
{
    QRegExp rx("("+argu+"\"\\s*value=\"\\S*\"\\s*/>)");
    rx.indexIn(html);
    QString tmp=rx.cap(1).replace(argu+"\" value=\"","").replace("\" />","");
    return encodeURI(tmp);
}

QByteArray Session::encodeURI(QString str)
{
    QByteArray outArr;
    QTextCodec *codec=QTextCodec::codecForLocale();
    QByteArray tmpArr;
    tmpArr = codec->fromUnicode(str);
    for(int i=0,size = tmpArr.length();i<size;i++){
        char ch = tmpArr.at(i);
        if((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){
            outArr.append(ch);
        }else{
            uchar low = ch & 0xff;
            char c[3];
            sprintf(c,"%02X",low);
            outArr.append("%").append(c);
        }

    }
    return outArr;
}

QString Session::getName(QString html)
{
    int s1=html.indexOf("xm=");
    int s2=html.indexOf("&gnmkdm");
    return html.mid(s1+3,s2-s1-3);
}

QList<QStringList> Session::query(QString years, QString term)
{
//    QUrl url=QUrl::fromEncoded(term.toLatin1());
//    term=QString(encodeURI(url.toString()));
    QTextCodec *gbk = QTextCodec::codecForName("gbk");
    term = gbk->fromUnicode(term).toPercentEncoding();
    if(!years.contains("20"))
    {
//        url=QUrl::fromEncoded(years.toLatin1());
//        years=QString(encodeURI(url.toString()));
        years=gbk->fromUnicode(years).toPercentEncoding();
    }

    request.setUrl(QUrl("http://"+m_host+"/("+m_tagCode+")/xscjcx_dq.aspx?xh="+m_id+"&xm="+m_name+"&gnmkdm=N121605"));
    QString refer="http://"+m_host+"/("+m_tagCode+")/xs_main.aspx?xh="+m_id;
    request.setRawHeader("Referer",refer.toLatin1());
    pReply=manager.get(request);
    loop.exec();
    QString html=pReply->readAll();

    delete pReply;

    QString viewState=getArgu("VIEWSTATE",html);
    QString eventvalidation=getArgu("EVENTVALIDATION",html);
    QByteArray data=QString("__EVENTTARGET=&__EVENTARGUMENT=&__LASTFOCUS=&__VIEWSTATE="+viewState+"&__EVENTVALIDATION="+eventvalidation+"&ddlxn="+years
                            +"&ddlxq="+
                            term+"&btnCx=+%B2%E9++%D1%AF+").toLatin1();
    pReply=manager.post(request,data);
    loop.exec();
    html=QString::fromLocal8Bit(pReply->readAll());
    delete pReply;
    QList<QStringList> list=getScore(html);
    return list;
}

QPixmap *Session::getCheckCode()
{
    request.setUrl(QUrl("http://"+m_host+"/("+m_tagCode+")/CheckCode.aspx"));
    pReply=manager.get(request);
    loop.exec();
    QByteArray data=pReply->readAll();
    QPixmap *pixmap=new QPixmap;
    pixmap->loadFromData(data);
    delete pReply;
    return pixmap;
}

QList<QStringList> Session::getScore( QString html )
{
    QRegExp rx("(<td>20(\\S*|\\s*)</td><td>(\\S*|\\s*)</td><td>(\\S*|\\s*)</td><td>\\S*\\s*\\S*</td><td>(\\S*|\\s*)</td><td>(\\S*|\\s*)</td><td>(\\S*|\\s*)</td><td>(\\S*|\\s*)</td><td>(\\S*|\\s*)</td><td>(\\S*|\\s*)</td><td>(\\S*|\\s*)</td><td>(\\S*|\\s*)</td><td>(\\S*|\\s*)</td><td>(\\S*|\\s*)</td><td>(\\S*|\\s*)</td><td>(\\S*|\\s*)</td>)");
    int pos=0,count=0;
    QString tmp;
    QStringList slist;
    QList<QStringList> list;
    while((pos=rx.indexIn(html,pos))!=-1)
    {
        count++;
        tmp=rx.cap(1);
        tmp.replace("<td>","");
        //	tmp.replace("</td></td></td>","");
        tmp.replace("&nbsp;","");
        slist=tmp.split("</td>");
        list<<slist;
        pos+=rx.matchedLength();
    }
    return list;
}
