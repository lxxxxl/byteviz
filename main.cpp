#include "bytesview.h"

#include <QApplication>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (argc == 2 && QFile::exists(argv[1])){
        BytesView v;
        QFile file(argv[1]);
        v.process(&file);
        v.show();
        return a.exec();
    }
    return -1;
}
