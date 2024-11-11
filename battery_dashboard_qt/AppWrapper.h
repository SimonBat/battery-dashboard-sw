#ifndef APPWRAPPER_H
#define APPWRAPPER_H

#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>
#include <QObject>
#include <QQmlContext>
#include "SerialPort.h"
#include "DataProfile.h"

class AppWrapper : public QObject
{
    Q_OBJECT
public:
    explicit AppWrapper(QObject *parent = nullptr);
    void initialize(void);

signals:

private slots:
    void resetQmlSerialPort(void);

private:
    QQuickView viewer;
    SerialPort *sPort;
    DataProfile *dataProfile;
};

#endif // APPWRAPPER_H
