#include "mainwnd.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(":/languages/language_en.qm");
    a.installTranslator(&translator);

    MainWnd w;
    w.setTranslator(&translator);
    w.showMaximized();

    return a.exec();
}
