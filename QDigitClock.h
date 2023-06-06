#ifndef QDIGITCLOCK_H
#define QDIGITCLOCK_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QResizeEvent>


class QDigitClock : public QWidget
{
    Q_OBJECT
public:
    QDigitClock(QWidget *parent = nullptr);

    void setBackgroundColor(QColor& color)  {background_color = color;}
    const QColor& getBackgroundColor() { return background_color;}

    void setDigitColor(QColor& color)  {digit_color = color;}
    const QColor& getDigitColor() { return digit_color;}

    void setValue(int hour, int min) {
        this->hour = hour;
        this->minute = min;

        digits[3] = minute % 10;
        digits[2] = minute / 10;
        digits[1] = hour % 10;
        digits[0] = hour / 10;

        update();
    }

signals:


protected:
    void paintEvent(QPaintEvent *event) override {
        QWidget::paintEvent(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPen pen(Qt::black, 2);
        painter.setPen(pen);

        QBrush brush(Qt::black);
        painter.setBrush(brush);

        drawDigit(digitPoint[0], digits[0], &painter);
        drawDigit(digitPoint[1], digits[1], &painter);
        drawDigit(digitPoint[2], digits[2], &painter);
        drawDigit(digitPoint[3], digits[3], &painter);
    }

    void drawDigit(QPoint* points, int value, QPainter* painter) {

        if (value == 0) {
            drawSeg1(points, painter);
            drawSeg2(points, painter);
            drawSeg3(points, painter);
            drawSeg4(points, painter);
            drawSeg5(points, painter);
            drawSeg6(points, painter);
        } else if (value == 1) {
            drawSeg2(points, painter);
            drawSeg3(points, painter);
        } else if (value == 2) {
            drawSeg1(points, painter);
            drawSeg2(points, painter);
            drawSeg7(points, painter);
            drawSeg4(points, painter);
            drawSeg5(points, painter);
        } else if (value == 3) {
            drawSeg1(points, painter);
            drawSeg2(points, painter);
            drawSeg3(points, painter);
            drawSeg4(points, painter);
            drawSeg7(points, painter);
        } else if (value == 4) {
            drawSeg2(points, painter);
            drawSeg3(points, painter);
            drawSeg6(points, painter);
            drawSeg7(points, painter);
        } else if (value == 5) {
            drawSeg1(points, painter);
            drawSeg3(points, painter);
            drawSeg4(points, painter);
            drawSeg6(points, painter);
            drawSeg7(points, painter);
        } else if (value == 6) {
            drawSeg1(points, painter);
            drawSeg3(points, painter);
            drawSeg4(points, painter);
            drawSeg5(points, painter);
            drawSeg6(points, painter);
            drawSeg7(points, painter);
        } else if (value == 7) {
            drawSeg1(points, painter);
            drawSeg2(points, painter);
            drawSeg3(points, painter);
        } else if (value == 8) {
            drawSeg1(points, painter);
            drawSeg2(points, painter);
            drawSeg3(points, painter);
            drawSeg4(points, painter);
            drawSeg5(points, painter);
            drawSeg6(points, painter);
            drawSeg7(points, painter);
        } else {
            drawSeg1(points, painter);
            drawSeg2(points, painter);
            drawSeg3(points, painter);
            drawSeg4(points, painter);
            drawSeg6(points, painter);
            drawSeg7(points, painter);
        }

    }

    void drawSeg1(QPoint* points, QPainter* painter) {
        QPolygon polygon;

        QPoint p0 = points[0] + QPoint(point_offset, 0);
        QPoint p1 = points[1] + QPoint(-point_offset, 0);

        polygon << p0;
        polygon << p0 + QPoint(dw05, -dw05);
        polygon << p1 + QPoint(-dw05, -dw05);
        polygon << p1;
        polygon << p1 + QPoint(-dw05, +dw05);
        polygon << p0 + QPoint(dw05, dw05);

        painter->drawPolygon(polygon);
    }

    void drawSeg2(QPoint* points, QPainter* painter) {
        QPolygon polygon;

        QPoint p0 = points[1] + QPoint(0, point_offset);
        QPoint p1 = points[2] + QPoint(0, -point_offset);

        polygon << p0;
        polygon << p0 + QPoint(dw05, dw05);
        polygon << p1 + QPoint(dw05, -dw05);
        polygon << p1;
        polygon << p1 + QPoint(-dw05, -dw05);
        polygon << p0 + QPoint(-dw05, dw05);

        painter->drawPolygon(polygon);
    }
    void drawSeg3(QPoint* points, QPainter* painter) {

        QPolygon polygon;

        QPoint p0 = points[2] + QPoint(0, point_offset);
        QPoint p1 = points[3] + QPoint(0, -point_offset);

        polygon << p0;
        polygon << p0 + QPoint(dw05, dw05);
        polygon << p1 + QPoint(dw05, -dw05);
        polygon << p1;
        polygon << p1 + QPoint(-dw05, -dw05);
        polygon << p0 + QPoint(-dw05, dw05);

        painter->drawPolygon(polygon);

    }
    void drawSeg4(QPoint* points, QPainter* painter) {

        QPolygon polygon;

        QPoint p0 = points[3] + QPoint(- point_offset, 0);
        QPoint p1 = points[4] + QPoint(point_offset, 0);

        polygon << p0;
        polygon << p0 + QPoint(-dw05, dw05);
        polygon << p1 + QPoint(dw05, dw05);
        polygon << p1;
        polygon << p1 + QPoint(dw05, -dw05);
        polygon << p0 + QPoint(-dw05, -dw05);

        painter->drawPolygon(polygon);

    }
    void drawSeg5(QPoint* points, QPainter* painter) {
        QPolygon polygon;

        QPoint p0 = points[4] + QPoint(0,- point_offset);
        QPoint p1 = points[5] + QPoint(0, point_offset);

        polygon << p0;
        polygon << p0 + QPoint(-dw05, -dw05);
        polygon << p1 + QPoint(-dw05, dw05);
        polygon << p1;
        polygon << p1 + QPoint(dw05, dw05);
        polygon << p0 + QPoint(dw05, -dw05);

        painter->drawPolygon(polygon);
    }
    void drawSeg6(QPoint* points, QPainter* painter) {
        QPolygon polygon;

        QPoint p0 = points[5] + QPoint(0,- point_offset);
        QPoint p1 = points[0] + QPoint(0, point_offset);

        polygon << p0;
        polygon << p0 + QPoint(-dw05, -dw05);
        polygon << p1 + QPoint(-dw05, dw05);
        polygon << p1;
        polygon << p1 + QPoint(dw05, dw05);
        polygon << p0 + QPoint(dw05, -dw05);

        painter->drawPolygon(polygon);
    }
    void drawSeg7(QPoint* points, QPainter* painter) {
        QPolygon polygon;

        QPoint p0 = points[2] + QPoint(- point_offset, 0);
        QPoint p1 = points[5] + QPoint(point_offset, 0);

        polygon << p0;
        polygon << p0 + QPoint(-dw05, dw05);
        polygon << p1 + QPoint(dw05, dw05);
        polygon << p1;
        polygon << p1 + QPoint(dw05, -dw05);
        polygon << p0 + QPoint(-dw05, -dw05);

        painter->drawPolygon(polygon);
    }

    void resizeEvent(QResizeEvent *event) override {
        QWidget::resizeEvent(event);

        QSize size = event->size();

        //int digit_w =
        //digitPoint[0][0] =

        int w = size.width();
        int h = size.height();

        int dh1 = h / 3;
        int dh2 = w / 7.6666;

        if (dh1 <= dh2) {
           dh = dh1;
        } else {
            dh = dh2;
        }

        dw = 0.3333*dh;
        dm = dw;

        int cent_x = w /2;
        int cent_y= h /2;

        point_offset = 5;
        dw05 = dw * 0.5;

        setPoints(digitPoint[0], QPoint(cent_x - (dw + dm + dh + dw + dm + dh), cent_y - dh));
        setPoints(digitPoint[1], QPoint(cent_x - (dw + dm + dh), cent_y - dh));
        setPoints(digitPoint[2], QPoint(cent_x + (dw + dm), cent_y - dh));
        setPoints(digitPoint[3], QPoint(cent_x + (dw + dm + dh + dw + dm), cent_y - dh));

        update();
    }

    void setPoints(QPoint* digit, QPoint top_left) {
        digit[0] = top_left;
        digit[1] = top_left + QPoint(dh, 0);
        digit[2] = top_left + QPoint(dh, dh);
        digit[3] = top_left + QPoint(dh, 2 * dh);
        digit[4] = top_left + QPoint(0, 2 * dh);
        digit[5] = top_left + QPoint(0, dh);
    }

protected slots:
    void onTimer() {
        setValue(hour, minute+1);
    }


private:
    QColor background_color;
    QColor digit_color;

    int dh;
    int dm;
    int dw;
    int dw05;
    int point_offset;

    QPoint digitPoint[4][6];
    int digits[4];

    int hour;
    int minute;

    QTimer timer;

};

#endif // QDIGITCLOCK_H
