#ifndef QSOUNDSOURCE_H
#define QSOUNDSOURCE_H

#include <QObject>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QTimer>
#include <QThreadPool>
#include <QAudioSink>
#include <QMediaDevices>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>

}

//https://github.com/ArthurEmidio/audioplayer/blob/master/src/audioplayer.c#L225


class FFppegRunnable : public QObject, public QRunnable {
    Q_OBJECT
public:
    FFppegRunnable(QString url) {


    }


    void ffmpegOpenInput() {

    }




    void play_ffmpeg() {

        mPlayer = new QMediaPlayer(NULL);
        audioOutput = new QAudioOutput(NULL);

        mPlayer->setAudioOutput(audioOutput);

        //QObject::connect(mPlayer, &QMediaPlayer::errorOccurred, this, &FFppegRunnable::errorOccurred);

        setVolume(100);


        //av_register_all();

        pFormatContext = avformat_alloc_context();

        AVDictionary *options = NULL;

        // Ustawia wartość rtbufsize na 100M
        av_dict_set(&options, "rtbufsize", "10M", 0);
        //av_dict_set(&options, "itsoffset", "5", 0);



            if (avformat_open_input(&pFormatContext,
                                    "http://stream3.polskieradio.pl:8900/"
                                    //"d:\\sample.mp3"
                                    //"d:\\StarWars60.wav"
                                    //"http://www2.cs.uic.edu/~i101/SoundFiles/StarWars60.wav"
                                    , NULL, &options) != 0) {
                qInfo() << "Could not open file";
                return;
            }

            //av_dict_free(&options);

            if (avformat_find_stream_info(pFormatContext, NULL) < 0) {
                qInfo() << "Could not retrieve stream info";
                return;
            }

            // Szukamy strumienia audio
                audioStreamIndex = -1;
                for (int i = 0; i < pFormatContext->nb_streams; i++) {
                    if (pFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
                        audioStreamIndex = i;
                        break;
                    }
                }

                if (audioStreamIndex == -1) {
                    qInfo() << "Could not find an audio stream";
                    return;
                }

                // Uzyskujemy kontekst kodera
                AVCodecParameters *pLocalCodecParameters = pFormatContext->streams[audioStreamIndex]->codecpar;
                const AVCodec *pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);

                pCodecContext = avcodec_alloc_context3(pLocalCodec);
                if (avcodec_parameters_to_context(pCodecContext, pLocalCodecParameters) < 0) {
                    qInfo() << "Could not set codec context parameters";
                    return;
                }

                if (avcodec_open2(pCodecContext, pLocalCodec, NULL) < 0) {
                    qInfo() << "Could not open codec";
                    return;
                }


                swr_context = swr_alloc_set_opts(nullptr,
                                                    av_get_default_channel_layout(2),
                                                    AV_SAMPLE_FMT_S16,
                                                    pCodecContext->sample_rate,
                                                    pCodecContext->channel_layout,
                                                    pCodecContext->sample_fmt,
                                                    pCodecContext->sample_rate,
                                                    0, nullptr);
                swr_init(swr_context);



                pPacket = av_packet_alloc();
                pFrame = av_frame_alloc();


                qInfo() << "sample rate " << pCodecContext->sample_rate;
                qInfo() << "channels " << pCodecContext->channels;

                //pCodecContext->sam




                QAudioFormat format;
                // Set up the format, eg.
                format.setSampleRate(pCodecContext->sample_rate);
                format.setChannelCount(pCodecContext->channels);
                format.setSampleFormat(QAudioFormat::Int16);



                //QAudioFormat format;
                // Set up the format, eg.
                //format.setSampleRate(8000);
                //format.setChannelCount(1);
                //format.setSampleFormat(QAudioFormat::UInt8);


                QAudioDevice info(QMediaDevices::defaultAudioOutput());
                    if (!info.isFormatSupported(format)) {
                        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
                        return;
                    }


                QAudioSink *audio = new QAudioSink(format, NULL);
                device = audio->start();

                if (!device) {
                    qInfo() << "duppaa";
                }

                //timer->start();




                /*
                QAudioDevice device = QMediaDevices::defaultAudioOutput();
                QAudioFormat format = device.preferredFormat();
                QAudioSink *output = new QAudioSink(device, format);
                QIODevice* dev = output->start();
                */




    }

    void run() override {

        play_ffmpeg();
        /*
            //AVPacket packet;
                //AVFrame *frame = av_frame_alloc();
                int response;

                while ((response = av_read_frame(pFormatContext, pPacket)) >= 0) {

                //qDebug() << "read_frame " << response;


                if (response >= 0) {
                    // Jeśli pakiet należy do strumienia audio
                    if (pPacket->stream_index == pCodecContext->channel_layout) {
                        // Dekodowanie pakietu i odtwarzanie
                        avcodec_send_packet(pCodecContext, pPacket);
                        while (avcodec_receive_frame(pCodecContext, pFrame) == 0) {
                            uint8_t *output_buffer;
                            int output_buffer_size = av_samples_alloc(&output_buffer, nullptr, 2, pFrame->nb_samples, AV_SAMPLE_FMT_S16, 0);
                            swr_convert(swr_context, &output_buffer, output_buffer_size, (const uint8_t **)pFrame->data, pFrame->nb_samples);

                            device->write((const char *)output_buffer, output_buffer_size);
                            av_freep(&output_buffer);
                        }
                    }
                    av_packet_unref(pPacket);
                }

                //av_frame_free(&frame);

                // Jeśli nie ma więcej ramek do odczytu, kończymy odtwarzanie
                if (response < 0) {
                    //audio_output->stop();
                } else {
                    // Inaczej, ponownie wywołujemy tę funkcję po krótkim okresie czasu
                    //QTimer::singleShot(0, this, &QSoundSource::OnTimer);
                }
            }

        */

        while (true) {
            //qDebug() << "OnTimer";
            // Czytamy pakiety z pliku

            int ret = 0;


            while ((ret = av_read_frame(pFormatContext, pPacket)) >= 0) {

                //qDebug() << "read frame " << ret;

                if (pPacket->stream_index == audioStreamIndex) {
                    // Dekodujemy pakiet
                    if (avcodec_send_packet(pCodecContext, pPacket) < 0) {
                        qDebug() << "Could not decode packet";
                        return;
                    }



                    while (avcodec_receive_frame(pCodecContext, pFrame) == 0) {

                        //device->write((char*)pFrame->data[0], pFrame->linesize[0]);


                        uint8_t *output_buffer;
                        int output_buffer_size = av_samples_alloc(&output_buffer, nullptr, 2, pFrame->nb_samples, AV_SAMPLE_FMT_S16, 0);
                        swr_convert(swr_context, &output_buffer, output_buffer_size, (const uint8_t **)pFrame->data, pFrame->nb_samples);

                        device->write((const char *)output_buffer, output_buffer_size);
                        av_freep(&output_buffer);

                    }
                }

                //Time time = pPacket->time_base;

                av_packet_unref(pPacket);

                //
            }

             if (ret == AVERROR_EOF) {
                qDebug() << "EOF" << ret;

             }

            qDebug() << "read frame " << ret;

            QThread::msleep(10);

            //av_seek_frame(pFormatContext, audioStreamIndex, 0, 0);

        }
    }

public slots:
    void setVolume(int vol) {
        audioOutput->setVolume(vol);
    }

    void errorOccurred(QMediaPlayer::Error error, const QString &errorString) {
        qDebug() << error << " " << errorString;
    }

private:
    QAudioOutput* audioOutput;
    QMediaPlayer *mPlayer;

    AVFormatContext *pFormatContext;
    AVPacket *pPacket;
    AVFrame *pFrame;
    int audioStreamIndex;

    SwrContext *swr_context = nullptr;

    QIODevice *device;
    AVCodecContext *pCodecContext;
};



class QSoundSource : public QObject
{
    Q_OBJECT
public:
    QSoundSource(QObject *parent = nullptr);

    void openFile(const QString& filename) {
        //mPlayer->setSource(QUrl(filename));
        //mPlayer->play();
    }

    void play_ffmpeg();


public slots:


    void OnTimer ();

signals:

protected:
    QTimer *timer;




};





#endif // QSOUNDSOURCE_H
