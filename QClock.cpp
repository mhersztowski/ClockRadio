#include "QClock.h"

QClock::QClock(QObject *parent)
    : QObject{parent}
{

    timer.setInterval(1000);
    QObject::connect(&timer, &QTimer::timeout, this, &QClock::onTimer);
}

void QClock::onTimer() {
    QDateTime current = QDateTime::currentDateTime();

    curr_min = current.time().minute();
    curr_hour = current.time().hour();
    emit timeChange(curr_hour, curr_min);
    checkAlarms();

}

void QClock::checkAlarm(QTime& time) {
    if (time.hour() == curr_hour && time.minute() == curr_min) {
        emit alarmExecute();
    }
}

void QClock::checkAlarms() {
    checkAlarm(alarm[0]);
    checkAlarm(alarm[1]);
    checkAlarm(alarm[2]);
    checkAlarm(alarm[3]);
    checkAlarm(alarm[4]);
}
