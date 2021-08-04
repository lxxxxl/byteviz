#include "bytesview.h"

BytesView::BytesView(QWidget *parent)
    : QGraphicsView(parent)
{
    // setup alignment
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    // add QGraphicsScene to view
    this->setScene(&scene);
}

void BytesView::process(QFile *file)
{
    if (!file->open(QFile::ReadOnly))
        return;
    // TODO
    // do not read whole file
    bytes = file->readAll();

    drawBytes(bytes.mid(currentIndex, bufferSize));

    file->close();
}

void BytesView::drawByte(int x, int y, uchar value)
{
    // setup color with specified hue according to byte value
    QColor color;
    color.setHsv(value, 100, 150);
    // add rect to apropriate coordinates
    scene.addRect(
                QRectF(x * byteWidth, y * byteHeight, byteWidth, byteHeight),
                QPen(color),
                QBrush(color));
}

void BytesView::drawBytes(QByteArray bytes)
{
    int x, y, counter;
    int count = bytes.size();
    x = 0;
    y = 0;

    // cleanup QGraphicsScene
    scene.clear();

    for (counter = 0; counter < count; counter++){
        drawByte(x, y, bytes.at(counter));
        if (++x >= bytesPerLine){
            x = 0;
            y++;
        }
    }

    // update screen
    this->viewport()->update();
}

void BytesView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()){

    // scroll up by 1 line on Up
    case Qt::Key_Up:
        if (currentIndex >= bytesPerLine)
            currentIndex -= bytesPerLine;
        break;
    // scroll down by 1 line on Down
    case Qt::Key_Down:
        if (bytes.size() >= (currentIndex + bytesPerLine))
            currentIndex += bytesPerLine;
        break;
    // scroll one page up on PageUp
    case Qt::Key_PageUp:
        if (currentIndex >= bufferSize)
            currentIndex -= bufferSize;
        else
            currentIndex = 0;
        break;
    // scroll one page up on PageDown
    case Qt::Key_PageDown:
        if (bytes.size() >= (currentIndex + bufferSize))
            currentIndex += bufferSize;
        break;

    // increase count of bytes per line on Numpad+ press
    case Qt::Key_Plus:
        bytesPerLine += 1;
        break;

    // decrease count of bytes per line on Numpad- press
    case Qt::Key_Minus:
        bytesPerLine += 1;
        break;
    default:
        return;
    }
    // redraw bytes
    drawBytes(bytes.mid(currentIndex, bufferSize));
}

void BytesView::wheelEvent(QWheelEvent *event){
    QPoint numDegrees = event->angleDelta() / 8;
    // increase scale on scroll up
    if (numDegrees.y() > 0){
        // restrict max scale
        if ((byteWidth < 50) && (byteHeight < 100)){
            byteWidth += 5;
            byteHeight += 10;
        }
    }
    // decrease scale on scroll down
    else if (numDegrees.y() < 0){
        // restrict min scale
        if ((byteWidth > 5) || (byteHeight > 10)){
            byteWidth -= 5;
            byteHeight -= 10;
        }
    }
    // redraw bytes
    drawBytes(bytes.mid(currentIndex, bufferSize));

}

BytesView::~BytesView()
{
}

