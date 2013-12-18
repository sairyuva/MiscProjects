/* Author : Sandeep Manandhar <manandhar.sandeep@gmail.com>
 *This project is to create an image marker that can be used before
 *haar training to manually select the face region in number of picuters
 */
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
