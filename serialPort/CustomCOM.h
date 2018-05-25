#ifndef CUSTOMCOM_H
#define CUSTOMCOM_H

#include <QObject>
#include <QtSerialPort>

class CustomCOM : public QSerialPort
{
    Q_OBJECT

public:

    CustomCOM(qint32 baudRate, QObject* parent = 0);

private:

    bool initCOM(const QString& description);

public slots:

    void slotOpenCOM(QBitArray);

    void slotCloseCOM();

private:

    // Point array, transmitted to chart
    QByteArray XY;

private slots:

    // Collect point array and send it to chart as soon as it's full
    void slotXY(void);

signals:

    // Send signal with points to chart
    void signalXYforChart(const QByteArray);

    void signalCOMready(QBitArray);
};

#endif // CUSTOMCOM_H
