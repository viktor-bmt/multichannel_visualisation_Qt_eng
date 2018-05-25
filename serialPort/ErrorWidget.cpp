#include "ErrorWidget.h"

ErrorWidget::~ErrorWidget()
{
    if(ok)
        delete ok;
    if(text)
        delete text;
    if(layout)
        delete layout;
}

void ErrorWidget::setLabel(const QString& label)
{
    if (text)
        delete text;
    if (layout)
        delete layout;

    text = new QLabel(label);

    layout = new QVBoxLayout;
    layout->addWidget(text);
    layout->addWidget(ok);

    setLayout(layout);

    return;
}

void ErrorWidget::slotSerialError(QSerialPort::SerialPortError error)
{
    //qDebug() << error;

    switch(error)
    {
        case (QSerialPort::NoError):
        {
            break;
        }

        case (QSerialPort::PermissionError):
        {
            setLabel("<CENTER><B>Access denied</B></CENTER>"
                    "<CENTER>Terminate all MSP430 processes and try again</CENTER>");
            show();
            break;
        }

        case (QSerialPort::DeviceNotFoundError):
        {
            setLabel("<CENTER><B>Device not found</B></CENTER>"
                    "<CENTER>Connect MSP430 to the PC at first</CENTER>");

            show();
            break;
        }

        case (QSerialPort::ResourceError):
        {
            setLabel("<CENTER><B>Resource error</B></CENTER>"
                    "<CENTER>Possibly the connection with MSP430 is lost</CENTER>");

            show();
            break;
        }

        default:
        {
            setLabel("<CENTER><B>Unknown error</B></CENTER>"
                    "<CENTER>Restart the app</CENTER>");

            show();
        }
    }

    return;
}

void ErrorWidget::slotNoChecks()
{
    setLabel("<CENTER>Choose at least one curve to visualise</CENTER>");

    show();

    return;
}
