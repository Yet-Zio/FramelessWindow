#include "mainwindow.h"
#include "framelesswindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *mw = new MainWindow;

    FramelessWindow *w = new FramelessWindow;
    w->setCentralWidget(mw);
    w->setMenuBar(mw->getMenuBar());
    w->setTitle("Example");
    w->show();
    return a.exec();
}
