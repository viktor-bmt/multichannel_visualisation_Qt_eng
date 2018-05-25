#include "CheckWindow.h"

CheckWindow::CheckWindow(QWidget* parent /*= 0*/) :
    QWidget(parent),

    checkedCharts(8),

    pMainLayout(new QVBoxLayout),
    pButtonsLayout(new QHBoxLayout),
    pCheckLayout(new QGridLayout),

    pGroupCheck(new QGroupBox("Choose curves to visualise")),

    pOk(new QPushButton("OK")),
    pExit(new QPushButton("Exit"))
{
    pCheck[0] = new QCheckBox("Series of rect pulses");
    pCheck[1] = new QCheckBox("Three stage signal");
    pCheck[2] = new QCheckBox("Sine wave");
    pCheck[3] = new QCheckBox("Cosine wave");
    pCheck[4] = new QCheckBox("Series of triangular pulses");
    pCheck[5] = new QCheckBox("Sawtooth signal");
    pCheck[6] = new QCheckBox("Digital \"staircase\"");
    pCheck[7] = new QCheckBox("Electrocardiogram");

    pCheckLayout->setSpacing(10);

    pCheckLayout->addWidget(pCheck[0], 0, 0);
    pCheckLayout->addWidget(pCheck[1], 0, 1);
    pCheckLayout->addWidget(pCheck[2], 1, 0);
    pCheckLayout->addWidget(pCheck[3], 1, 1);
    pCheckLayout->addWidget(pCheck[4], 2, 0);
    pCheckLayout->addWidget(pCheck[5], 2, 1);
    pCheckLayout->addWidget(pCheck[6], 3, 0);
    pCheckLayout->addWidget(pCheck[7], 3, 1);

    pGroupCheck->setLayout(pCheckLayout);

    pButtonsLayout->addWidget(pOk);
    pButtonsLayout->addWidget(pExit);

    pMainLayout->setSpacing(20);
    pMainLayout->addWidget(pGroupCheck);
    pMainLayout->addLayout(pButtonsLayout);

    setLayout(pMainLayout);

    QObject::connect(pOk, SIGNAL(clicked()), this , SLOT(slotOKclicked()));
    QObject::connect(pExit, SIGNAL(clicked(bool)), this, SLOT(close()));
}

CheckWindow::~CheckWindow()
{
    for (int i = 0; i < 8; ++i)
    {
        if(pCheck[i])
            delete pCheck[i];
    }

    if(pOk)
        delete pOk;

    if(pExit)
        delete pExit;

    if(pCheckLayout)
        delete pCheckLayout;

    if(pButtonsLayout)
        delete pButtonsLayout;

    if(pGroupCheck)
        delete pGroupCheck;

    if(pMainLayout)
        delete pMainLayout;
}

void CheckWindow::slotOKclicked()
{
    bool flag = false;

    for (int i = 0; i < 8; ++i)
    {
        if (pCheck[i]->isChecked())
        {
            checkedCharts.setBit(i);
            flag = true;
        }
        else
            checkedCharts.clearBit(i);
    }

    if (flag)
        emit signalChartsChecked(checkedCharts);
    else
        emit signalNoChecks();
}
