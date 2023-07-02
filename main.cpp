#include <QApplication>
#include "MyDict.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyDict Dict;
    Dict.resize(300,530);
    Dict.show();
    return app.exec();
}
