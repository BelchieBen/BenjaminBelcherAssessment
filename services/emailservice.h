#ifndef EMAILSERVICE_H
#define EMAILSERVICE_H


#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>

/**
* This class contains all the methods to connect to gmail's smtp server and send emails to project members.
*/

class EmailService : public QObject
{
    Q_OBJECT


public:
    EmailService( const QString &user, const QString &pass,
          const QString &host, int port = 465, int timeout = 30000 );
    ~EmailService();

    void sendMail( const QString &from, const QString &to,
                   const QString &subject, const QString &body );

signals:
    void status( const QString &);

private slots:
    void stateChanged(QAbstractSocket::SocketState socketState);
    void errorReceived(QAbstractSocket::SocketError socketError);
    void disconnected();
    void connected();
    void readyRead();

private:
    int timeout;
    QString message;
    QTextStream *t;
    QSslSocket *socket;
    QString from;
    QString rcpt;
    QString response;
    QString user;
    QString pass;
    QString host;
    int port;
    enum states{Tls, HandShake ,Auth,User,Pass,Rcpt,Mail,Data,Init,Body,Quit,Close};
    int state;

};

#endif // EMAILSERVICE_H
