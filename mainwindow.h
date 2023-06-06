#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "QDigitClock.h"
#include "QSoundSource.h"
#include "logview.h"
#include <QWebEngineView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected:
    void resizeEvent(QResizeEvent *event) override {
        QMainWindow::resizeEvent(event);
        //digit_clock->resize(width(), height());
    }

private:
    QDigitClock* digit_clock;
    QSoundSource* sound_source;
    TrivialLogView* log_view;
    QWebEngineView* web_engine_view;
};
#endif // MAINWINDOW_H
