#ifndef BYTESVIEW_H
#define BYTESVIEW_H

#include <QGraphicsView>
#include <QFile>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QDebug>


class BytesView : public QGraphicsView
{
    Q_OBJECT

private:
    QGraphicsScene scene;
    // stores file's contents
    QByteArray bytes;
    // width of single byte's rectangle
    int byteWidth = 5;
    // height of single byte's rectangle
    int byteHeight = 10;
    // how many bytes should show in a line
    int bytesPerLine = 32;
    // how maby bytes should show on screen
    int bufferSize = 1024;
    // index of current displayable byte in bytes array
    int currentIndex = 0;


    void drawByte(int x, int y, uchar value);
    void drawBytes(QByteArray bytes);

    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);


public:
    BytesView(QWidget *parent = nullptr);
    void process(QFile *file);
    ~BytesView();
};
#endif // BYTESVIEW_H

