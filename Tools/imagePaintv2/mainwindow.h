#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QRubberBand>
#include "mygraphicsview.h"
#include <QKeyEvent>
#include <QDir>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loadImgBtn_clicked();
    void keyPressEvent(QKeyEvent *);
    void setPixScene(QString fileName);



    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_actionOpen_triggered();

    void on_actionAbout_triggered();

    void on_actionUsage_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPixmap image;
    QRubberBand *rubberBand;
    myGraphicsView *graphicsView;
    QStringList fileList;
    int curIndex, saveIndex;
    QDir dir;
    QFile *file;

};

#endif // MAINWINDOW_H
