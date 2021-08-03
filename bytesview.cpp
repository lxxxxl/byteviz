#include "bytesview.h"

BytesView::BytesView(QWidget *parent)
    : QGraphicsView(parent)
{
    // setup alignment
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

void BytesView::process(QFile *file)
{
    int x, y, counter;
    if (!file->open(QFile::ReadOnly))
        return;
    // TODO
    // do not read whole file
    QByteArray bytes = file->readAll();
    int count = bytes.size();
    x = 0;
    y = 0;
    for (counter = 0; counter < count; counter++){
        drawByte(x, y, bytes.at(counter));
        if (++x >= bytesPerString){
            x = 0;
            y++;
        }
    }

    file->close();

    // add graphics scene to QGraphicsView
    this->setScene(&scene);
    this->show();
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

BytesView::~BytesView()
{
}

