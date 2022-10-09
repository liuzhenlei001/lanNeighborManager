#ifndef LOCALHOST_H
#define LOCALHOST_H

#include <QObject>
#include <QMap>
#include <QString>

class LocalHost : public QObject
{
    Q_OBJECT
public:
    explicit LocalHost(QObject *parent = 0);

    static QMap<QString, QString> getAllInterfaces();

signals:

public slots:

private:

};

#endif // LOCALHOST_H
