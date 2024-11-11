#ifndef COMMCRC_H
#define COMMCRC_H

#include <QObject>

class CommCRC : public QObject
{
    Q_OBJECT
public:
    explicit CommCRC(QObject *parent = nullptr);

    quint16 calculateBufferCRC(QByteArray &data, quint16 length);
    quint16 calculateByteCRC(quint8 data, quint16 crc);

private:
    const static quint16 crc16ModbusTable[256];
};

#endif // COMMCRC_H
