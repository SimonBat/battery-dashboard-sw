#include "SerialPortLL.h"
#include <QDebug>

SerialPortLL::SerialPortLL(QObject *parent) : QObject(parent),
    thread(new QThread),
    sPort(new QSerialPort)
{
    connect(sPort, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));
    connect(sPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)),this, SLOT(errorOccurredSlot(QSerialPort::SerialPortError)));

    this->moveToThread(thread);
    sPort->moveToThread(thread);
    thread->start(QThread::HighestPriority);
}

SerialPortLL::~SerialPortLL()
{
    sPort->deleteLater();
    thread->quit();
    thread->wait();
    thread->deleteLater();
}

void SerialPortLL::writeDataSlot(QByteArray data)
{
    sPort->write(data);
}

void SerialPortLL::openPortStartSlot(QString portName)
{
    if(sPort->isOpen()){sPort->close();}
    // Open serial COM port
    sPort->setPortName(portName);
    sPort->setBaudRate(230400);
    sPort->setDataBits(QSerialPort::Data8);
    sPort->setParity(QSerialPort::NoParity);
    sPort->setStopBits(QSerialPort::OneStop);
    sPort->setFlowControl(QSerialPort::NoFlowControl);
    if(sPort->isOpen()){sPort->close();}
    emit openPortEndSignal(sPort->open(QIODevice::ReadWrite));
}

void SerialPortLL::closePortSlot()
{
    if(sPort->isOpen()){sPort->close();}
}

void SerialPortLL::readyReadSlot()
{
    // Get data from serial port
    QByteArray data = sPort->readAll();
    emit readyReadSignal(data);
}

void SerialPortLL::errorOccurredSlot(QSerialPort::SerialPortError error)
{
    if((QSerialPort::ResourceError == error) || (QSerialPort::UnsupportedOperationError == error) || \
        (QSerialPort::PermissionError == error) || (QSerialPort::DeviceNotFoundError == error))
    {
        emit errorOccurredSignal();
    }
}
