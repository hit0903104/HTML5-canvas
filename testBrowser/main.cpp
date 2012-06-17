#include <QtCore>
#include <QtGui>
#include "testbrowser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    testBrowser *browser = new testBrowser;
    browser->show();

    return a.exec();
}
