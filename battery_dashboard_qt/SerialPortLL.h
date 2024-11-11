#ifndef SERIALPORTLL_H
#define SERIALPORTLL_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

class SerialPortLL : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortLL(QObject *parent = nullptr);
    ~SerialPortLL();

public slots:
    void writeDataSlot(QByteArray data);
    void openPortStartSlot(QString portName);
    void closePortSlot(void);

signals:
    void readyReadSignal(QByteArray data);
    void errorOccurredSignal(void);
    void openPortEndSignal(bool status);

private slots:
    void readyReadSlot();
    void errorOccurredSlot(QSerialPort::SerialPortError error);

private:
    QThread *thread;
    QSerialPort *sPort;
};

#endif // SERIALPORTLL_H
