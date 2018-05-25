#include "CustomCOM.h"

CustomCOM::CustomCOM(qint32 baudRate, QObject* parent /*= 0*/) :
    QSerialPort(parent)
{
    setBaudRate(baudRate);
    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(slotXY()));
}

bool CustomCOM::initCOM(const QString& COMDescription)
{
    clearError();

    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
    bool flag = false;

    foreach(QSerialPortInfo port, list)
    {

        // if (port.description() == COMDescription) // For Windows (Tested on Win10)
        if (port.portName() == COMDescription) // For Linux (Tested on Linux Mint 18.3)
        {
            flag = true;

            setPort(port);
            if(open(QIODevice::ReadWrite))
            {
                clear();
                return true;
            }

            return false;
        }
    }

    if (!flag)
    {
        emit error(QSerialPort::DeviceNotFoundError);
        return false;
    }

    return false;
}

void CustomCOM::slotXY(void)
{
    if (bytesAvailable())
        XY.append(read(8 - XY.size()));

    if(XY.size() == 8)
    {
        emit signalXYforChart(XY);
        XY.clear();
    }

    return;
}

void CustomCOM::slotOpenCOM(QBitArray arr)
{
    // if (initCOM("MSP Application UART1")) // For Windows (Tested on Win10)
    if (initCOM("ttyACM1")) // For Linux (Tested on Linux Mint 18.3)
        emit signalCOMready(arr);

    return;
}

void CustomCOM::slotCloseCOM()
{
    close();

    return;
}
