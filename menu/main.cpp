#include "src/MainWindow/mainwindow.h"
//#include <QApplication>
#include <QtSingleApplication>
#include <QDesktopWidget>
#include <QFile>
#include "ukuimenuinterface.h"

int main(int argc, char *argv[])
{
//    QApplication app(argc, argv);
    QtSingleApplication app("ukui-start-menu",argc,argv);
    app.setQuitOnLastWindowClosed(false);
    if(app.isRunning())
    {
        app.sendMessage("raise_window_noop");
        return EXIT_SUCCESS;
    }

    QFile qss(":/data/qss/kylin-start-menu.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());

    MainWindow w;
    app.setActivationWindow(&w);
//    w.move(0,a.desktop()->height()-w.height());
    w.setGeometry(QRect(0,QApplication::desktop()->availableGeometry().height()-532,390,532));

    w.show();
    w.raise();
    w.activateWindow();

    return app.exec();
}
