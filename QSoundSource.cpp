#include "QSoundSource.h"
#include <QTimer>

QSoundSource::QSoundSource(QObject *parent)
    : QObject{parent}
{
    //timer = new QTimer(this);
    //timer->setInterval(100);
    //QObject::connect(timer, &QTimer::timeout, this, &QSoundSource::OnTimer);


    QThreadPool *pool = QThreadPool::globalInstance();

    pool->start(new FFppegRunnable("test"));

}




void QSoundSource::OnTimer () {



}

