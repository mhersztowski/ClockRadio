#include "QDigitClock.h"

QDigitClock::QDigitClock(QWidget *parent)
    : QWidget{parent}, hour(0), minute(0)
{

    digits[0] = 0;
    digits[1] = 0;
    digits[2] = 0;
    digits[3] = 0;

    timer.setInterval(1000);
    QObject::connect(&timer, &QTimer::timeout, this, &QDigitClock::onTimer);
    timer.start();
}
