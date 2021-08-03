#ifndef BYTESVIEW_H
#define BYTESVIEW_H

#include <QGraphicsView>
#include <QFile>

class BytesView : public QGraphicsView
{
    Q_OBJECT

private:
    QGraphicsScene scene;
    int byteWidth = 5;
    int byteHeight = 10;
    int bytesPerString = 16;

    void drawByte(int x, int y, uchar value);


public:
    BytesView(QWidget *parent = nullptr);
    void process(QFile *file);
    ~BytesView();
};
#endif // BYTESVIEW_H

