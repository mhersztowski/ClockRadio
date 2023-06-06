#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    resize(1333, 716);

    //digit_clock = new QDigitClock(this);
    //digit_clock->resize(300, 150);

    log_view = new TrivialLogView(this);
    log_view->resize(1333, 716);

    sound_source = new QSoundSource(this);

    //sound_source->openFile("qrc:/sound/data/StarWars60.wav");

    //sound_source->openFile("http://www2.cs.uic.edu/~i101/SoundFiles/StarWars60.wav");

    //mms://stream.polskieradio.pl/program1

    //sound_source->openFile("http://stream3.polskieradio.pl:8900");
    //sound_source->openFile("http://mp3.polskieradio.pl:8900");
    //sound_source->openFile("http://217.74.72.12/rmf_fm");
    //sound_source->openFile("d:/StarWars60.wav");

    //web_engine_view = new QWebEngineView(this);
    //web_engine_view->load(QUrl("https://player.polskieradio.pl/anteny/jedynka/"));
    //setCentralWidget(web_engine_view);
}

MainWindow::~MainWindow()
{
}

