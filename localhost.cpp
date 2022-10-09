#include "localhost.h"
#include <QNetworkInterface>
#include <QDebug>

LocalHost::LocalHost(QObject *parent) : QObject(parent)
{
    ;
}

QMap<QString, QString> LocalHost::getAllInterfaces()
{
    QMap<QString, QString> interfaces_map;

    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for(int i = 0; i < interfaces.size(); ++i)
    {
//        qDebug()<<interfaces.at(i).humanReadableName()<<","<<interfaces.at(i).hardwareAddress();
        QList<QNetworkAddressEntry> entries = interfaces.at(i).addressEntries();
        for(int j = 0; j < entries.size(); ++j)
        {
            QNetworkAddressEntry entry = entries.at(j);
            QHostAddress ipItem = entry.ip();
            if(ipItem.protocol() == QAbstractSocket::IPv4Protocol
                    && ipItem != QHostAddress::Null
                    && ipItem != QHostAddress::LocalHost)
            {
                interfaces_map[interfaces.at(i).humanReadableName()] = ipItem.toString();
//                qDebug()<<"    "<<ipItem.toString()<<","<<entry.netmask().toString()<<","<<entry.broadcast().toString();
            }
        }
    }

    return interfaces_map;
}
