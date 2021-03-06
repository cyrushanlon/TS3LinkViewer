#include <QPointer>
#include <QApplication>
#include <QtWebEngine>
#include <QWebEngineSettings>

#include "widget.h"

#define RESTART_CODE 1337

int main(int argc, char *argv[])
{
    int ReturnCode;
    QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);

    QPointer<QApplication> App;
    QPointer<Widget> MainWin;

    do
    {
        if(App) App->quit();
        if(MainWin) delete MainWin;

        App = new QApplication(argc, argv);
        MainWin = new Widget();
        ReturnCode = App->exec();
    }
    while(ReturnCode == RESTART_CODE);

    return ReturnCode;
}
