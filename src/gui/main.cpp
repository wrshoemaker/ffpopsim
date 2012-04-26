/**
 * @file main.cpp
 * @brief Main loop of the QT GUI for PopGenLib
 * @author Richard Neher, Boris Shraiman, Fabio Zanini
 * @version 
 * @date 2012-04-26
 */
#include <QtGui/QApplication>
#include "mainwindow.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow mainwindow;
    mainwindow.show();
    return app.exec();
}
