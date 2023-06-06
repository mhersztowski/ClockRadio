#ifndef QCLOCK_H
#define QCLOCK_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

class QClock : public QObject
{
    Q_OBJECT
public:
    QClock(QObject *parent = nullptr);

signals:
    void timeChange(int hour, int min);
    void alarmExecute();

protected slots:
    void onTimer();

protected:
    int curr_min;
    int curr_hour;
    QTimer timer;

    QTime alarm[5];

    void checkAlarm(QTime& time);
    void checkAlarms();
};

#endif // QCLOCK_H
