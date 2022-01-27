#include "Widget/Widget.h"

#include <QApplication>
#include <QThreadPool>
#include <QMessageBox>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <string>
#include <iostream>
#include <QTextCodec>

#include <windows.h>
#include <DbgHelp.h>
#include <strsafe.h>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    if(!QDir().exists("CAN-ADAS.dbc"))
    {
        QMessageBox::warning(nullptr, "错误", "未找到 CAN-ADAS.dbc");
        return -1;
    }

    Widget w;
    w.show();

    return a.exec();
}
